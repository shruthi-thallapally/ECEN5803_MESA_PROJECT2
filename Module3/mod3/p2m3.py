
"""
/********************************************************************

* @see <a href="https://www.gnu.org/software/bash/manual/">Bash Reference Manual</a>
* @see <a href="https://docs.python.org/3/library/os.html">Python OS Library Documentation</a>
********************************************************************/
"""

import os
import platform
import time

# Directory where output files will be saved
output_directory = "/home/pi/Documents/MESA/project2/mod3"


def show_menu():
    """
    Displays the menu options for system information retrieval.
    The menu is displayed for informational purposes.
    """
    menu_options = {
        "1": "List all Running Process",
        "2": "Get Kernel Name",
        "3": "Get Kernel Version",
        "4": "Get Kernel Dump",
  	    "5": "Get device IP",
  	    "6": "Show all active processes",
        "7": "Show all background processes",
        "8": "Number of processes per user",
        "9": "Real time Linux Monitoring",
        "10": "Real time Disk Utilization",
        "11": "Real time Memory Consumption",
        "12": "Show RAM Stats",
        "13": "Get Physical Memory Stats",
        "14": "Get Swap Memory Stats",
        
    }

    print("###########################################################")
    for key, value in menu_options.items():
        print(f"{key}. {value}")
    print("###########################################################")

def execute_command(command, output_file):
    """
    Executes a system command and redirects the output to a specified file.
    
    Args:
    command (str): The system command to be executed.
    output_file (str): The name of the file where the command output will be saved.
    """
    full_command = f'{command} > {output_directory}/{output_file}'
    os.system(full_command)


def main():
    """
    Main function to execute system information commands and save their outputs.
    Each command's output is saved to a distinct text file.
    """
    show_menu()

    # Execute commands and save outputs to files
    execute_command('ps aux', '1_running_processes.txt')
    execute_command('uname --kernel-name', '2_kernel_name.txt')
    execute_command('uname --kernel-version', '3_kernel_version.txt')
    execute_command('dmesg', '4_kernel_dump.txt')
    execute_command("ifconfig | grep 'broadcast' | awk '{print $2}'", '5_device_ip.txt')
    execute_command('ps aux', '6_active_processes.txt')
    execute_command('ps aux | grep "^[^ ]* S"', '7_background_processes.txt')
    execute_command('ps -e -o user= | sort |uniq -c', '8_no_of_processes.txt')
    execute_command('top -b -n 1', '9_real_time_linux_monitoring.txt')
    execute_command('df -h', '10_disk_utilization.txt')
    execute_command('free -m', '11_memory_consumption.txt')
    execute_command('lscpu', '12_ram_stats.txt')   
    execute_command("free -m | grep 'Mem' | awk '{print  \"Physical Memory Stats in MB: \", \"Total:\", $2,  \"Used:\", $3,\"Free:\", $4, \"Shared:\", $5,\"Buff/Cache:\", $6, \"Available:\", $7}'", '13_physical_memory_stats.txt')
    execute_command("free -m | grep 'Swap' | awk '{print  \"Swap Memory Stats in MB: \", \"Total:\", $2,  \"Used:\", $3,\"Free:\", $4, \"Shared:\", $5,\"Buff/Cache:\", $6, \"Available:\", $7}'", '14_swap_memory_stats.txt')


if __name__ == "__main__":
    main()

