# OS-deadlock-avoidance-banker-algorithm

<p>
  In this project I made a simulation for the bankers algorithm which is used by some opreating systems to avoid deadlocks.
  
  <h2>You can do the following with it:</h2>
  
  <h3>Check if a system is safe or not</h3>
  
  It will check if the system is safe or not if not then there is a deadlock and it has to resolve it, I have chosen the victim based
  on how many resources it is holding so, the one with the most resources is the victim.
  
  <h4>Safe Testcase</h4>
  
  ![](https://github.com/AdelBenAshraf/OS-deadlock-avoidance-banker-algorithm/blob/main/gifs/trying.gif)
  
  <h4>UnSafe Testcase</h4>
  
  ![](https://github.com/AdelBenAshraf/OS-deadlock-avoidance-banker-algorithm/blob/main/gifs/deadlock_testcase.gif)

  <h3>Request more resources</h3>
  
  You can request more resources for a specific process, then the program will check if the system can handle it or not,
  after that if it can handle it, it will check if it is safe or not, if it is not safe it will resolve the deadlock and then proceed.
  
  ![](https://github.com/AdelBenAshraf/OS-deadlock-avoidance-banker-algorithm/blob/main/gifs/request.gif)
  
  <h3>Release resources</h3>
  
  You can release resources for a specific process.
  
  ![](https://github.com/AdelBenAshraf/OS-deadlock-avoidance-banker-algorithm/blob/main/gifs/release.gif)
</p>
