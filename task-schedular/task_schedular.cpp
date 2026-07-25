#include <bits/stdc++.h>
using namespace std;

enum TaskState {
    PENDING,
    RUNNING,
    COMPLETED,
    FAILED,
    CANCELLED
};

enum TaskPriority {
    LOW,
    MEDIUM,
    HIGH
};

struct Task {
    int id;
    TaskState state = TaskState::PENDING;
    function<void()> execution_payload;
    TaskPriority priority = TaskPriority::MEDIUM;
    vector<int> parentTasks;
    int sequence_number;
};

struct TaskComparator {
    bool operator()(const Task &a, const Task &b) const {
        if (a.priority != b.priority) {
            return a.priority < b.priority;
        }
        return a.sequence_number > b.sequence_number;
    }
};

/*
Yes, [this] is required inside the lambda captures list.

Here is why:

The Problem
Inside backgroundRunner(), the lambda checks two member variables of the TaskSchedular class:

taskQueue (i.e., this->taskQueue)

stopSchedular (i.e., this->stopSchedular)

[this]() { 
    return !taskQueue.empty() || stopSchedular; 
}
Because backgroundRunner() is a member function, taskQueue and stopSchedular belong to the class instance (this).

In C++, a lambda function is an isolated, anonymous object. It cannot see or access any class variables outside its parameter list unless you explicitly pass/capture them!

What happens if you remove this?
If you write []() instead of [this]():

C++
// ❌ COMPILE ERROR
cv.wait(ulock, []() {
    return !taskQueue.empty() || stopSchedular;
});
The C++ compiler will throw an error like:

error: 'taskQueue' was not declared in this scope

error: 'stopSchedular' was not declared in this scope

Summary
[]: Lambda captures nothing. It cannot access any variables outside itself.

[this]: Gives the lambda access to the current class instance, allowing it to read and write member variables (taskQueue, stopSchedular, etc.) seamlessly!

*/



class TaskSchedular {
    unordered_map<int, vector<int>> adjList;
    unordered_map<int, Task> taskDetails; // this is the task details
    unordered_map<int, int> indegreesOfTasks;
    priority_queue<Task, vector<Task>, TaskComparator> taskQueue;
    mutex mtx;
    thread backgroundWorker;
    bool stopSchedular = false;
    condition_variable cv;
    int seq_num = 0;

    void backgroundRunner() {
        while (true) {
            Task topTask;
            {
                unique_lock<mutex> ulock(mtx); // we need to use the cv.wait() in this thats why we have used unique_lock and also unique_lock has Highly flexible (Can lock and unlock manually anytime). Slightly heavier (Stores lock status flag).

                cv.wait(ulock, [this]() {
                    return !taskQueue.empty() || stopSchedular;
                });

                if (stopSchedular && taskQueue.empty()) return;

                topTask = taskQueue.top();
                taskQueue.pop();
                taskDetails[topTask.id].state = TaskState::RUNNING;
            }

            bool success = processTask(topTask);

            {
                lock_guard<mutex> lLock(mtx); // This lock will be Rigid (Locks on creation, unlocks on destruction). and extremely lighweight than unique_lock but in this cv.wait() is not suported

                if (success) {
                    taskDetails[topTask.id].state = TaskState::COMPLETED;
                    for (int neigh : adjList[topTask.id]) {
                        indegreesOfTasks[neigh]--;
                        if (indegreesOfTasks[neigh] == 0) {
                            taskQueue.push(taskDetails[neigh]);
                            cv.notify_one();
                        }
                    }
                } else {
                    taskDetails[topTask.id].state = TaskState::FAILED;
                    cancelSubtree(topTask.id);
                }
            }
        }
    }

    void cancelSubtree(int node) {
        for (int neigh : adjList[node]) {
            if (taskDetails[neigh].state == TaskState::PENDING) {
                taskDetails[neigh].state = TaskState::CANCELLED;
                cancelSubtree(neigh);
            }
        }
    }

    // 3-State DFS Cycle Detector to handle complex DAG paths accurately
    bool detectCycleDFS(int node, unordered_map<int, vector<int>> &adj, unordered_map<int, int> &visited) {
        visited[node] = 1; // 1 = VISITING (In active recursion stack)

        for (int neigh : adj[node]) {
            if (visited[neigh] == 1) return true; // Cycle found
            if (visited[neigh] == 0) {
                if (detectCycleDFS(neigh, adj, visited)) return true;
            }
        }

        visited[node] = 2; // 2 = VISITED (Fully processed)
        return false;
    }

public:
    TaskSchedular() {
        stopSchedular = false;
        backgroundWorker = thread(&TaskSchedular::backgroundRunner, this);
        cout << "Constructor call ended" << endl;
    }

    ~TaskSchedular() {
        {
            lock_guard<mutex> lock(mtx);
            stopSchedular = true;
        }
        cv.notify_all();
        if (backgroundWorker.joinable()) {
            backgroundWorker.join();
        }
    }

    bool processTask(Task &task) {
        for (int parentTaskId : task.parentTasks) {
            if (taskDetails[parentTaskId].state == TaskState::FAILED) {
                taskDetails[task.id].state = TaskState::CANCELLED;
                return false;
            }
        }
        if (task.execution_payload) {
            task.execution_payload();
        }
        taskDetails[task.id].state = TaskState::COMPLETED;
        return true;
    }

    bool submitTask(Task &task, vector<int> &parentTaskIds) {
        lock_guard<mutex> lock(mtx);

        unordered_map<int, vector<int>> tempAdjList = adjList;
        int taskIndegree = parentTaskIds.size();

        bool allCompleted = true;

        for (int i = 0; i < parentTaskIds.size(); i++) {
            tempAdjList[parentTaskIds[i]].push_back(task.id);
            if (taskDetails.count(parentTaskIds[i]) && taskDetails[parentTaskIds[i]].state != TaskState::COMPLETED) {
                allCompleted = false;
            } else if (taskDetails.count(parentTaskIds[i]) && taskDetails[parentTaskIds[i]].state == TaskState::COMPLETED) {
                taskIndegree--;
            }
        }

        unordered_map<int, int> visitedState;
        if (detectCycleDFS(task.id, tempAdjList, visitedState)) {
            return false;
        }

        adjList = tempAdjList;

        task.sequence_number = seq_num;

        seq_num++;

        task.parentTasks = parentTaskIds;

        taskDetails[task.id] = task;

        taskDetails[task.id].state = TaskState::PENDING;

        if (allCompleted) {
            taskQueue.push(task);
            cv.notify_one();
            indegreesOfTasks[task.id] = -1;
        } else {
            indegreesOfTasks[task.id] = taskIndegree;
        }

        return true;
    }

    TaskState getTaskStatus(int taskId) {
        lock_guard<mutex> lock(mtx);
        if (taskDetails.count(taskId)) {
            return taskDetails[taskId].state;
        }
        return TaskState::FAILED;
    }

    Task getTaskDetails(int taskId) {
        lock_guard<mutex> lock(mtx);
        return taskDetails[taskId];
    }
};

int main() {
    TaskSchedular ts;
    
    Task t;
    t.execution_payload = [](){
        cout<<"This is the lambda function";
    };

    t.priority = TaskPriority::HIGH;
    
    vector<int> parentIds = {};
    ts.submitTask(t,parentIds);

    Task task;

    task = (ts.getTaskDetails(0));

    cout<<task.id<<endl;
    cout<<task.priority<<endl;
    cout<<task.sequence_number<<endl;


    Task t2 ;

    t2.priority = TaskPriority::LOW;

    t2.execution_payload = [](){
        cout<<"This is the T2 Lambda function"<<endl;
    };

    vector<int> parentIdsT2 = {};

    ts.submitTask(t2,parentIdsT2);


    Task task2;
     task2 = (ts.getTaskDetails(1));

    cout<<task2.id<<endl;
    cout<<task2.priority<<endl;
    cout<<task2.sequence_number<<endl;
}