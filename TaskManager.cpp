
#include "TaskManager.h"

TaskManager::TaskManager() = default;

void TaskManager::assignTask(const string &personName, const Task &task) {
    Task newTask = task;
    newTask.setId(m_newestTaskId++);

    Person* curPerson = findPerson(personName);
    if (curPerson == nullptr) {
        curPerson = addPerson(personName);
    }
    curPerson->assignTask(newTask);
}

void TaskManager::completeTask(const string &personName) {
    if (Person* curPerson = findPerson(personName)) {
        curPerson->completeTask();
    }
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if (priority > 0) {
        for (unsigned int i = 0; i < m_numOfPersons; ++i) {
            Person& curPerson = m_personArray[i];
            const SortedList<Task>& curTaskList = curPerson.getTasks();
            SortedList<Task> newTaskList = curTaskList.apply([&type, &priority](const Task& curTask) -> Task {
                if (curTask.getType() == type) {
                    const int newPriority = curTask.getPriority() + priority;
                    Task newTask(newPriority, curTask.getType(), curTask.getDescription());
                    newTask.setId(curTask.getId());
                    return newTask;
                }
                return curTask;
            });
            curPerson.setTasks(newTaskList);
        }
    }
}

void TaskManager::printAllEmployees() const {
    for (unsigned int i = 0; i < m_numOfPersons; ++i) {
        std::cout << m_personArray[i] << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    const SortedList<Task> listOfAllTasks = createListOfAllTasks();
    const SortedList<Task> listToPrint = listOfAllTasks.filter([&type](const Task& curTask) -> bool {
        if (curTask.getType() == type) {
            return true;
        }
        return false;
    });
    printTaskList(listToPrint);
}

void TaskManager::printAllTasks() const {
    printTaskList(createListOfAllTasks());
}

// -------------------------------- helpers -------------------------------- //

Person* TaskManager::findPerson(const string &personName) {
    for (Person& curPerson : m_personArray) {
        if (curPerson.getName() == personName) {
            return &curPerson;
        }
    }

    return nullptr;
}

Person *TaskManager::addPerson(const string &personName) {
    if (m_numOfPersons >= MAX_PERSONS) {
        throw std::runtime_error("Max Number of People Reached");
    }
    m_personArray[m_numOfPersons++] = Person(personName);

    return &m_personArray[m_numOfPersons - 1];
}

SortedList<Task> TaskManager::createListOfAllTasks() const {
    SortedList<Task> newListOfTasks;
    for (unsigned int i = 0; i < m_numOfPersons; ++i) {
        const Person& curPerson = m_personArray[i];
        const SortedList<Task>& curTaskList = curPerson.getTasks();
        for (const Task& curTask : curTaskList) {
            newListOfTasks.insert(curTask);
        }
    }

    return newListOfTasks;
}

void TaskManager::printTaskList(const SortedList<Task> &listToPrint) {
    for (const Task& curTask : listToPrint) {
        std::cout << curTask << std::endl;
    }
}
