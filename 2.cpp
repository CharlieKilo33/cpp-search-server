#include <iostream>
#include <map>
#include <tuple>

enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};

using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks {
public:
    TasksInfo GetPersonTasksInfo(const std::string &person) {
        return persons_tasks[person];
    }

    void AddNewTask(const std::string &person) {
        persons_tasks[person][TaskStatus::NEW]++;
    }

    std::tuple<TasksInfo, TasksInfo>
    PerformPersonTasks(const std::string &person, int task_count) {
        TasksInfo updated_tasks, untouched_tasks;
        untouched_tasks = persons_tasks[person];

        if(persons_tasks[person].empty()){
            return {updated_tasks, untouched_tasks};
        }

        int &new_tasks = persons_tasks[person][TaskStatus::NEW];
        int &in_progress_tasks = persons_tasks[person][TaskStatus::IN_PROGRESS];
        int &testing_tasks = persons_tasks[person][TaskStatus::TESTING];
        int &done_tasks = persons_tasks[person][TaskStatus::DONE];

        for (int i = 0; i < task_count; ++i) {
            if (new_tasks > 0) {
                --new_tasks;
                ++in_progress_tasks;
                untouched_tasks[TaskStatus::NEW]--;
                updated_tasks[TaskStatus::IN_PROGRESS]++;
            } else if (in_progress_tasks - updated_tasks[TaskStatus::IN_PROGRESS] > 0) {
                --in_progress_tasks;
                ++testing_tasks;
                untouched_tasks[TaskStatus::IN_PROGRESS]--;
                updated_tasks[TaskStatus::TESTING]++;
            } else if (testing_tasks - updated_tasks[TaskStatus::TESTING] > 0) {
                --testing_tasks;
                ++done_tasks;
                untouched_tasks[TaskStatus::TESTING]--;
                updated_tasks[TaskStatus::DONE]++;
            }
        }

//        for(auto it = untouched_tasks.begin(); it != untouched_tasks.end(); ){
//            if(!it->second){
//                it = untouched_tasks.erase(it);
//            } else {
//                it++;
//            }
//        }

        TasksInfo copy_updated_tasks, copy_untouched_tasks;

        for(const auto& [status, value] : updated_tasks){
            if(value){
                copy_updated_tasks[status] = value;
            }
        }

        for(const auto& [status, value] : untouched_tasks){
            if(value && status != TaskStatus::DONE){
                copy_untouched_tasks[status] = value;
            }
        }

        return {copy_updated_tasks, copy_untouched_tasks};
    }

private:
    std::map<std::string, TasksInfo> persons_tasks;
};


void PrintTasksInfo(TasksInfo tasks_info) {
    std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
              ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
              ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
              ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main() {
    TeamTasks tasks;
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    };
    std::cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 3);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 3);
    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
}