# multi-task-rpi2
Basic examples for multi-task program implemented in rpi2

### td1a

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp main_td1a.cpp -o td1a.rpi2 -lrt -lpthread

./td1a.rpi2
```

### td1b

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp main_td1b.cpp -o td1b.rpi2 -lrt -lpthread

./td1b.rpi2
```

### td1c

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp main_td1c.cpp -o td1c.rpi2 -lrt -lpthread

./td1c.rpi2 <nLoops>
```

### td1d

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp main_td1d.cpp -o td1d.rpi2 -lrt -lpthread

./td1d.rpi2
```

### td1e

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp main_td1e.cpp -o td1e.rpi2 -lrt -lpthread

 ./td1e.rpi2
```

### td2a

```bash
arm-linux-g++ -Wall -Wextra main_td2a.cpp -o td2a.rpi2  -lrt -lpthread

./td2a.rpi2 <nLoops> <nTasks>
```

### td2b

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp main_td2b.cpp -o td2b.rpi2  -lrt -lpthread

./td2b.rpi2 <nLoops> <nTasks> <Policy>
```

### td2c

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp main_td2c.cpp -o td2c.rpi2  -lrt -lpthread

./td2c.rpi2 <nLoops> <nTasks> <protected>
```



### td3a

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp Chrono.cpp main_td3a.cpp -o td3a.rpi2 -lrt -lpthread

./td3a.rpi2 
```

### td3b

```bash
arm-linux-g++ -Wall -Wextra Timer.cpp TimeUtils.cpp Looper.cpp Chrono.cpp Calibrator.cpp main_td3b.cpp -o td3b.rpi2 -lrt -lpthread

./td3b.rpi2 
```

### td3c

```bash
arm-linux-g++ -Wall -Wextra Timer.cpp TimeUtils.cpp Chrono.cpp Calibrator.cpp Looper.cpp CpuLoop.cpp main_td3c.cpp -o td3c.rpi2 -lrt -lpthread

./td3c.rpi2 
```



### td4a

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp Mutex.cpp Thread.cpp main_td4a.cpp PosixThread.cpp IncrMutex.cpp Chrono.cpp IncrThread.cpp -o td4a.rpi2 -lrt -lpthread

./td4a.rpi2 <loop number> <task number>
```



### td4b

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp Mutex.cpp Thread.cpp main_td4b.cpp PosixThread.cpp IncrMutex.cpp Chrono.cpp -o td4b.rpi2 -lrt -lpthread

./td4b.rpi2 <loop number> <task number>
```

### td4c

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp Mutex.cpp Thread.cpp main_td4c.cpp PosixThread.cpp Semaphore.cpp JetonThread.cpp Chrono.cpp -o td4c.rpi2 -lrt -lpthread

./td4c.rpi2 <nConsumer> <nProducer>
```

### td4d

```bash
arm-linux-g++ -Wall -Wextra TimeUtils.cpp Mutex.cpp Thread.cpp main_td4d.cpp PosixThread.cpp Fifo.hpp ConProdFifo.cpp Chrono.cpp -o td4d.rpi2 -lrt -lpthread

./td4d.rpi2 <nConsumer> <nProducer>
```

### td5

```bash
arm-linux-g++ -Wall -Wextra Calibrator.cpp Chrono.cpp CpuLoop.cpp CpuLoopMutex.cpp Looper.cpp main_td5.cpp Mutex.cpp PosixThread.cpp Thread.cpp TimeUtils.cpp Timer.cpp -o td5.rpi2 -lrt -lpthread

./td5.rpi2 
```

