# HacklOSsim: FreeRTOS

## Table of Contents

1. [Introduction](#introduction)
2. [Project Description](#project-description)
3. [System Requirements](#system-requirements)
4. [Installation Guide](#installation-guide)
5. [Before Coding in FreeRTOS](#freeRtos-coding)
6. [Run & Debug a FreeRTOS Project](#freertos-testing)
7. [FreeRTOS Functionalities](#freeRtos-functionalities)
8. [EDF Scheduler](#edf-scheduler)
9. [Multilevel Queue Scheduler](#multilevel-queue-scheduler)
10. [Group Members](#group-members)



## 1. Introduction

This document provides an overview of the [FreeRTOS Embedded OS](https://www.freertos.org/FreeRTOS-quick-start-guide.html) as part of the university project for the Computer Architecture & Operating System course of the Politecnico di Torino Cybersecurity Master's Degree.

This README file contains:
- A tutorial detailing the installation and usage procedures to code in FreeRTOS while using the [Qemu ISA Emulator](https://www.qemu.org/);
- A description of the main functionalities offered by FreeRTOS, which are further explained in the ***HacklOSsim Report*** file and by the various ***.c*** files located in the folder:
> ./Freertos/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC
- An introduction to the changes needed to implement a _new_ [EDF Scheduler](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling) and a _new_ [Multilevel Queue Scheduler](https://en.wikipedia.org/wiki/Multilevel_queue) (see ***HacklOSsim Report*** for details);



## 2. Project Description

The project is designed to gain proficiency in using Qemu to run the FreeRTOS embedded OS. Thanks to the developed examples we are able to demonstrate the basic functionalities of FreeRTOS, in alignment with the topics studied in class. Furthermore, the newly developed EDF and Multilevel Queue schedulers were properly evaluated and benchmarked in order to report any performance improvement over the original solutions of FreeRTOS.



## 3. System Requirements

**Beware!** This project was developed using **only** Windows Operative Systems while and the _Installation Guide_ works **only** for Windows 10/11 OS. Other OSs may require different programs or tools to make Qemu and FreeRTOS work correctly.



## 4. Installation Guide

Follow the steps below to install the Qemu and FreeRTOS, please **note**: the download order of the various programs is **not** to be strictly followed. However, for time efficiency reasons, it is **strongly** recommended to download everything **before** adding the various programs to the _User PATH environment_:

1. Download and install [Visual Studio Code](https://code.visualstudio.com/download);
2. Download and install [Qemu](https://www.qemu.org/download/) (requires also the download and installation of [MYSYS2](https://www.msys2.org/));
3. Download and install the [Arm GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain);
4. Download and install [CMake](https://cmake.org/download/);
5. Download and install [Git](https://git-scm.com/downloads);
6. Download and install the ***make*** _tool_ using [Chocolatey](https://chocolatey.org/);

If you do **not** have Chocolatey on your system, take a look at the _Installation Guide_ to know how to install it through the Windows PowerShell;

7. Add **Qemu**, **Arm GNU Toolchain**, **CMake** and the ***make*** _tool_ to the _User Path Environment_;

Now you have all the required tools to make the FreeRTOS project work. 

You can proceed by cloning the GitLab project repo and opening the folder with _VSCode_: since the project was developed using Qemu, all the project related code is located into the folder:
> ./Freertos/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC



## 5. Before Coding in FreeRTOS

If you want to start a new _"blank"_ project on FreeRTOS, follow these steps:

1. Using the Windows PowerShell navigate to the folder where you want to save FreeRTOS repo;
2. Type: 
> git clone https://github.com/FreeRTOS/FreeRTOS.git –recurse-submodules
3. Once the cloning of the FreeRTOS repo has finished, open the folder in VSCode and navigate to the folder:
> ./Freertos/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC/.vscode
Here you will have to modify two files in order to make FreeRTOS and Qemu work together in your system:
- Open ***launch.json*** and modify the path contained in the line starting with **"miDebuggerPath"** to the path that leads to the **arm-none-eabi-gdb.exe** of the _Arm GNU Toolchain_;
- Open ***task.json***, go to line **22** and **delete everything that comes after**:
> "echo ’QEMU RTOSdemo started’; qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel ${workspaceFolder}/build/gcc/output/RTOSDemo.out"

Check the content of these files even if you just want to test and/or modify our project.



## 6. Run & Debug a FreeRTOS Project

In order to run and debug a FreeRTOS project that uses Qemu, you need to:
1. Click on the ***"Run and Debug"*** button located in the top lest bar of VSCode;
2. Press the **green arrow** while ***"Launch QEMU RTOS Demo"*** is selected to start the program;
3. Once Qemu has opened, select **View --> serial0** to view the printouts of your tasks;



## 7. FreeRTOS Functionalities

FreeRTOS provides robustness, tiny footprint, detailed pre-configured demos, Internet of Things (IoT) reference integrations and scalable size. In addition, FreeRTOS has a minimal ROM, RAM and processing overhead and it is very simple. 

Most notably, the ***FreeRTOSConfig.h*** file allows the user to perform crucial configuration arrangements, as it contains key settings which influence the behavior of FreeRTOS within a specific application.

Below is a brief list of some configurations that are found inside it:
- **Kernel Settings**:
    - Maximum task priority;
    - Queue size;
    - Characteristics of the timer management system;
- **Memory Management**: memory allocation and deallocation functions used by FreeRTOS;
- **Optimization Options**: enable or disable specific features of FreeRTOS;
- **Error Handling**: configurations on how FreeRTOS should handle errors and asserts;
- **Scheduler**: can be set to use the **Priority Based Preemptive Scheduler** or the **Round-Robin** one. To showcase their behavior the **RoundRobin.c** and **Preemptive.c** demo files can be found in the folder:
> ./Freertos/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC

FreeRTOS implements a series of data structures and associated functions, such as:
- **Tasks**: FreeRTOS is designed as a **single-processor OS** where, given a set of **independent Tasks**, **only one** can be at the Running state at any point in time. The **Real-Time Scheduler** is responsible for deciding which task should be executed and to ensure that the **Context Switch** is performed correctly. To achieve this, each task is provided with:
    - Its own **Stack**;
    - A priority level, ranging from **0** to (**configMAX_PRIORITIES - 1**). Lower values indicate tasks with lower priority;
- **Semaphores**: FreeRTOS provides two kinds of Semaphores...
    - **Binary Semaphores**: while Binary Semaphores differ subtly from **Mutexes**, as they feature a priority inheritance mechanism, whereas Binary Semaphores do **not**. Therefore, Binary Semaphores are preferable for **synchronization tasks**, while Mutexes excel at **simple mutual exclusion tasks**;
    - **Counting Semaphores**: they can be visualized as Queues with a length greater than one. They are primarily used for:
        - Counting events;
        - Resource management;
        
    ***semphr.h*** is the library that provides data types and several functions in order to use and manage Semaphores. It is necessary to include it in order to use it. The ***semphr.h*** defines the following data structure and functions:
    - A semaphore should be defined as a global variable such as **SemaphoreHandle\_t sem**;
    - **SemaphoreHandle\_t xSemaphoreCreateBinary()**: creates a Binary Semaphore, and returns a handle by which the semaphore can be referenced. The semaphore is created in the _'empty'_ state, meaning the semaphore **must** first be _'given'_ using the **xSemaphoreGive()** API function before it can subsequently be _'taken'_ by a task using the **xSemaphoreTake()** function;
    - **SemaphoreHandle\_t xSemaphoreCreateCounting(int MAX\_VAL, int initialVal)**: creates a Counting Semaphore and returns a handle by which the newly created semaphore can be referenced;
    - **xSemaphoreTake(SemaphoreHandle\_t xSemaphore, TickType\_t xTicksToWait)**: used to _'take'_ a semaphore. **xTicksToWait** is the time in ticks to wait for the semaphore to become available;
    - **xSemaphoreGive(SemaphoreHandle\_t xSemaphore)**: used to _'give'_ a semaphore;
    - **SemaphoreHandle\_t xSemaphoreCreateMutex()**: creates a Mutex, and returns a handle by which the created Mutex can be referenced. Mutexes **cannot** be used in interrupt service routines. Mutexes are _'taken'_ using **xSemaphoreTake()**, and _'given'_ using **xSemaphoreGive()**;
- **Queues**: they are fundamental for enabling communication between tasks in a multitasking system. They serve as channels through which tasks can exchange messages, facilitating coordination and data sharing. Typically, Queues operate on a first-in-first-out (FIFO) basis,meaning that the data sent earlier is received first. However, it is also possible to send data to the front of the Queue if necessary. The ***queue.c*** defines all the data structures and functions related to the Queues:
    - **QueueCreate()**: used to create the Queue in the main. It takes two parameters:
        -  The maximum size (number of items) of the Queue;
        -  The size of each item in the Queue;
    The functions returns a handle of type **QueueHandle_t**, which represents the newly created Queue;
    - **queueSendTask() & xQueueSend()**: this function reads one character at a time from the string **STRING_TO_SEND** and, using the **xQueueSend()** function pushes the character into the Queue, and takes three parameters:
        - **QueueHandle_t xQueue**: the handle of the Queue to which you want to send the item;
        - **\*const void pvItemToQueue**: pointer to the item to send to the Queue. This parameter is of type **const void \***, meaning it can be a pointer to any type of data. FreeRTOS does **not** directly perform any operations on the data but allows sending any type of data through Queues;
        - **TickType_t xTicksToWait**: maximum wait period for the send operation. If the Queue is full at the time of sending, the function waits for a specified period of time before returning a result. 
    - **queueReceiveTask() & xQueueReceive()**: extracts a character from the head of the Queue using the function **xQueueReceive()**, and then prints it to the screen. The **xQueueReceive()** function is used to receive an element (or a message) from a Queue, and function takes three parameters:
        - **QueueHandle_t xQueue**: handle of the Queue from which you want to receive the element;
        - **void \* pvBuffer**: pointer to the buffer where the received element from the Queue will be stored. Since FreeRTOS allows sending any type of data through Queues, **pvBuffer** can be a pointer to any type of data. It's the programmer's responsibility to ensure that the buffer is large enough to hold the received element;
        - **TickType_t xTicksToWait**: maximum wait time for the receive operation. If the Queue is empty at the time of receive, this function waits for a specified period of time before returning a result;
- **Events**: FreeRTOS provides two kinds of Events...
    - **Event Bits** or **Event Flags**: they are used to indicate whether an event has occurred or not. They can be defined as individual bits that take on a specific value to represent the state of an event;
    - **Event Groups**: they are sets of Event Bits, where each bit is identified by a bit number. The API functions for event groups allow tasks to set, clear, and wait for one or more event bits to be set within an event group. They can also be used to synchronize tasks, creating synchronization points where tasks wait until all other involved tasks have reached their synchronization points;

The ***event_groups.c*** defines all the data structures and functions related to the Events:
- **xEventGroupCreate()**: used to create a new event group and returns a handle (**EventGroupHandle_t**) that can be used to access the created event group;
- **xEventGroupWaitBits()**: this function suspends the execution of the current task until at least one or all of the specified bits are set in the event group. It takes five parameters, the most important are:
    - **const EventGroupHandle_t xEventGroup**: the handle of the event group to wait for the bits to be set;
    - **const EventBits_t uxBitsToWaitFor**:  the bits that the current task is waiting to be set;
    - **TickType_t xTicksToWait**: the maximum time in ticks for which the task will remain suspended waiting for the bits to be set before returning;
- **xEventGroupSetBits()**: this function sets specific bits in the event group;

Further insight on these data structure and their related functions can be found in the ***.h*** and ***.c*** files located in the folder:
> ./Freertos/FreeRTOS/Source

Moreover, a number of examples has been developed in order to properly showcase the usefulness and capabilities of these data structures. These examples can be found in the folder:
> ./Freertos/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC



## 8. EDF Scheduler

The **EDF** algorithm is a scheduling policy used in real-time systems to schedule tasks based on their deadlines, ensuring that tasks with closer deadlines are executed first, **reducing the likelihood of missing deadlines** and **improving overall system performance**. Additionally, EDF can further optimize scheduling thanks the use of **preemption** and of dynamic priority assignment.

In our implementation of EDF algorithm we wanted to:
- Maintain FreeRTOS’s original structure;
- Handle _aperiodic tasks_ as soft real-time systems with a **Background Scheduling** approach;

All the changes we had to perform are explained in the ***HacklOSsim Report*** file and all the modified code sections of FreeRTOS are available in the **Freertos/FreeRTOS** folder and subfolders. 

To enable the use of the EDF scheduler, a configuration parameter named **configUSE_EDF** has been added to ***FreeRTOSConfig.h*** which has to be configured in the following way:
```
#define configUSE_PREEMPTION		1
#define configUSE_TIME_SLICING          0
#define EDF_aperiodic_count             (VALUE)
#define configUSE_EDF                   1
#define INCLUDE_xTaskAbortDelay		1
```

In short, the main modifications that were performed on FreeRTOS mainly concern the ***task.c*** file:
- **TCB Modification**: the variable **TickType_t xTaskDeadline** (line 385) is added to the Task Control Block (TCB) to store the deadline;
- **Task Creation Function**: a new task creation function, **xTaskCreateEDF()**, has been introduced to accommodate the deadline parameter. This function accepts a **TickType_t** parameter for the deadline. The deadline value is stored in the TCB for later use (line 1787);
- **Ready List**: tasks are scheduled based on their deadlines. A single list, **xReadyTasksListsEDF**, is used to arrange tasks in ascending order of deadlines (line 6353);
- **Deadline & Priority Updates**: the **prvAddTaskToReadyList** function has been modified to update task deadlines when tasks are inserted into the ready list. The deadline is recalculated as the sum based on the previously deadline and the declared deadline value in the TCB;
- **Preemption**: the new policy for the preemption is implemented in the **xTaskIncrementTick** function (line 5066);
- **Context Switching**: a new policy for the context switching is needed, according with the new implemented ready list, the task that will be executed is the first in the **xReadyTasksListsEDF** _earliest deadline list_ (line 5451);
- **IDLE Task Management**: in the EDF scheduler, the IDLE task is assigned a deadline representing the farthest deadline. This ensures that the IDLE task executes **only** when no other tasks are ready. So a new global variable representing the _IDLE deadline_ (**initDeadline**) is added (line 120). Then **xTaskCreateEDF** is used to create the IDLE task (line 3810);
- **Aperiodic Task Management**: aperiodic tasks are managed within the same ready list as periodic tasks, with a slight adjustment to their deadlines and are created with a dedicated **vTaskCreate xTaskCreateEDFaperiodic** function (line 1834). Aperiodic tasks are inserted into the ready list with a fictitious deadline earlier than the one of the IDLE task (line 1852);

The ***HacklOSsim Report*** file also contains the evaluation of the performance improvement achieved by the newly implemented EDF scheduler, this benchmarks have been obtained using the [Cheddar Scheduling Simulator](http://beru.univ-brest.fr/cheddar/) and various demos to showcase its use are included in the folder:
> ./Freertos/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC



## 9. Multilevel Queue Scheduler

The **Multilevel Queue Scheduler** utilizes 5 basic FreeRTOS's lists, each associated with a different priority level. The first four lists, including one for the IDLE task, operate on a priority basis with preemptive scheduling but **without** time slicing. **Only** the highest priority (fifth) list operates on a round-robin basis.

Context Switch occur **only** when a higher priority task is added to the Ready List or when the running task is blocked or suspended.

Additionally, every 10 ticks, tasks in the Ready List increase in priority until they reach the highest priority list with round-robin scheduling. 

Upon suspension, a task leaves the Ready List and its initial priority is restored.

In order to use the Multilevel Queue, the ***FreeRTOSConfig.h*** file must be configured as follows:
```
#define configUSE_PREEMPTION		0
#define configUSE_sched2                1
#define configUSE_EDF                   0
#define configUSE_TIME_SLICING          0
#define INCLUDE_xTaskAbortDelay		0
```

It also possible to configure the period after which the priority of the tasks in the Ready List is increased, by setting a proper **value**:
```
#define tick_update_rate                (value)
```

Enabling the Multilevel Queue scheduler applies the following modifications of the ***task.c*** file of FreeRTOS:
- **TCB Modification**: the **UBaseType_t uxOldPriority** variable is added to the TCB to store the old priority of a task. The **int cc** is also added to the TCB, but it has **only** an internal purpose (line 391);
- **Task Creation Function**: the variables that are added to TCB are initialized in the xTaskCreate: 
```
pxNewTCB->cc = 0;
pxNewTCB->uxOldPriority = uxPriority;
```
Where **uxPriority** is the priority given from the user to the task (line 1760);
- **xTaskPrioritySet**: a smaller version of the **vTaskPrioritySet** has been added in order to properly modify the priority of a task (line 4857):
```
void xTaskPrioritySet( TCB_t * pxTCB, UBaseType_t uxNewPriority )
```
- **Highest Priority List Round Robin**: the **xTaskIncrementTick** function has been modified in order to implement round-robin on the highest priority list. Round-robin is activated when there are **at least** two task inside the list (line 4961). The policy to restore the priority of a task when it is reinserted into the ready list has also been integrated in the **xTaskIncrementTick** function (line 5031);
- **Priority Upgrade**: the **xTaskIncrementTick** function has also been modified in order to update a task's priority. When the system ticks reach a multiple of the **UPDATE_RATIO**, every task in the ready list (except the one currently running) gets a priority boost (**priority + 1**) using the **xTaskPrioritySet** function (line 5090);

Various demos to showcase its use can be found in the folder:
> ./Freertos/FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC



## 10. Group Members

The project was developed by **Group 20**, composed of:

- **Sannia Gabriele - S331385** [s331385@studenti.polito.it]
- **Sabella Mattia Luigi - S285363** [s285363@studenti.polito.it]
- **Pittalis Domenico - S283602** [s283602@studenti.polito.it]
- **Nobili Luca - S331461** [s331461@studenti.polito.it]