# GrooveOS

Presentation Link: https://uconn-my.sharepoint.com/:p:/g/personal/krishveer_grewal_uconn_edu/EdIz5ln1HolAiFWxY84yhJMB8_h3LYQQdtPibHNM0kuRPg?e=YDudzz

GrooveOS is a modular, microkernel-style operating system implemented C++.
It is designed for real-time embedded applications (audio devices, grooveboxes) but can also run as a standalone OS simulation on Linux.

GrooveOS is composed of:

- **Kernel**
- **Task Manager** (cooperative scheduler)
- **MessageBus** (publish/subscribe IPC)
- **DriverManager**
- **SysLog** (persistent event log)
- **Shell** (interactive CLI task)

---

### **Kernel**
- System initialization and boot sequence
- Memory structures and global state
- Launching and coordinating essential subsystems
- Providing the main update loop for cooperative scheduling

---

### **Task Manager**    
- Adds, removes, and runs tasks in round-robin order
- Tasks yield voluntarily (non-preemptive)
- Designed for deterministic execution — ideal for realtime audio/controller systems
- Each task implements a simple interface: `update()` called each cycle

---

### **MessageBus**  
- Publish messages to named topics
- Subscribe tasks/drivers to topics
- Fully decouples producers from consumers
- Used internally for logging, driver events, shell messages, and more

## **DriverManager**
- Driver initialization and teardown
- Driver lifecycle management
- Allowing the kernel and shell to query available drivers
- Providing a consistent interface for hardware or simulated device drivers

Drivers can publish events to the MessageBus or expose command interfaces.

---

### **SysLog**
- Stores kernel events, driver messages, and system warnings
- Viewable via the `log` command in the Shell
- Helpful for tracing MessageBus operations or driver activity

---

### **Shell**
- Built-in commands (`help`, `ps`, `drivers`, `log`, etc.)
- Ability to send messages over the MessageBus
- Debug/inspection tools for runtime state
- A minimal text-based UI, similar to an embedded device console

---

### Build
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
## Run

```bash
./grooveos
```

### Commands
```bash
help #show available commands
ps #list all scheduled tasks
drivers #list all registered drivers
log #view system log buffer
send <topic> <message> #publish an ipc message to the MessageBus
shutdown #exit OS
```


