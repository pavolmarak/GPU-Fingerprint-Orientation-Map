# GPU Fingerprint Orientation Map
Qt project containing a program to demonstrate GPU-based fingerprint orientation map (O-map) calculation. The program executes a performance test of O-map calculation on CPU/GPU backend. During the test, a reference square image size is increased by a constant factor of 50 pixels in both dimensions. Following this, the image's O-map is computed 50 times in a row. This procedure repeats after we hit 3000x3000 size. Average processing times for CPU/GPU are plotted on screen. The measurement below was taken on PC with i7-7700K and NVIDIA Geforce GTX 1080 Ti Founder's Edition Inno3D (without overclocking).

This project depends on the following **3rd-party libraries**:
* ArrayFire 3.5.1 (minimum), CUDA backend version, minimum CUDA 8.0 
* OpenCV 3.4.1 (tested)
* QCustomPlot 2.0.0 (tested)

![alt text](img/performance.png "CPU vs. GPU performance comparison graph")
