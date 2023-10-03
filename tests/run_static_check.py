from subprocess import run

try:
    run("make sensor_mock", shell=True, check=True)
    run("valgrind --leak-check=full ./sensor_mock", shell=True, check=True)
    run("make clean", shell=True, check=True)
except:
    pass