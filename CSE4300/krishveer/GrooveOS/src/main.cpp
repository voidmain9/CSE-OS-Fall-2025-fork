#include "kernel/Kernel.h"
#include "apps/Shell.h"
#include "kernel/MessageBus.h"
#include "drivers/ConsoleDriver.h"


int main() {
    auto& kernel = Kernel::instance();
    kernel.driverManager().registerDriver(
        std::make_unique<ConsoleDriver>(kernel.messageBus())
    );
    kernel.boot();

    MessageBus& bus = kernel.messageBus();  
    Shell shell(kernel, bus);

    kernel.taskManager().addTask("Shell", 200, [&shell]() {
        shell.tick();
    });

    kernel.run();
    return 0;
}
