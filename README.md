# ECE 6460 Homework #1
The goal of this assignment is to subscribe to the ground-truth velocity data coming from a Gazebo simulation of an autonomous vehicle, copy the forward speed data and re-publish it on a different ROS topic.

The purpose of this assignment is to:

- Ensure the student's PC is set up properly for the course
- Practice writing simple ROS nodes
- Introduce the workflow procedure of submitting homework assignments through GitHub Classroom

## Due Date
This assignment is due on Sunday, September 22nd at midnight.

## Provided Files
After accepting the assignment on GitHub Classroom, the student's assignment repository will be initialized with the following files:

- Pre-configured `package.xml` and `CMakeLists.txt` files for the `homework1` package
- Template C++ files to be modified as part of the assignment:
	- `src/homework1_node.cpp`
	- `src/Homework1.cpp`
	- `src/Homework1.hpp`
- Test configuration files in the `tests` folder of the `homework1` package

## Requirements
Modify the starting files to implement the following requirements. The breakdown of the number of grading points is shown in square brackets.

### 1. Copy and Re-publish vehicle speed [75 / 100]
Modify `Homework1.cpp` and `Homework1.hpp` to:
- Subscribe to the `/vehicle/twist` topic, which is of type `geometry_msgs/TwistStamped`
- Advertise the `/vehicle_speed` topic with type `std_msgs/Float64`
- Whenever a `geometry_msgs/TwistStamped` message is received on the `/vehicle/twist` topic, copy the vehicle's forward speed into a `std_msgs/Float64` message and publish it on the `/vehicle_speed` topic.

### 2. Pass Automated Tests [25 / 100]
Make sure the automated test script runs and reports that all tests passed. See Step 4 below for how to run the test locally on your computer.

## Hints

### Step 1: Clone this Repository

Clone this repository to your computer using either GitKraken or the command line by following along with the homework submission workflow video: [https://youtu.be/SGEYUezQ3QY?si=u4sg1wBxEzxdFkaz](https://youtu.be/SGEYUezQ3QY?si=u4sg1wBxEzxdFkaz)

### Step 2: Implement Required Changes

Modify the starting ROS node source files to implement Requirement #1.

### Step 3: Compile and Test Manually
#### 3.1 Run catkin_make
After making the required changes to the starting ROS node source files, compile the ROS workspace using the `release.bash` script:

```
cd ~/ros
release.bash
```
#### 3.2 Launch the System
If the compiling process finished successfully, proceed to manually test the modified ROS node by starting up the simulator and the `homework1` node. First, start a `roscore` in its own terminal window / tab:
```
roscore
```

In a new terminal window, launch the simulator and the `homework1` node at the same time:
```
roslaunch homework1 homework1.launch
```
#### 3.3 View ROS Topic Contents
Look at the `/vehicle/twist` topic by opening a new terminal window and using `rostopic echo`:

```
rostopic echo /vehicle/twist
```

Make sure the `linear.x` component of the twist message matches the `/vehicle_speed` topic by opening another terminal window and echoing it:

```
rostopic echo /vehicle_speed
```
After verifying that your node modifications are working as they should, stop the simulation before moving on to Step 3.

### Step 4: Run the Automated Tests Locally
To run the same tests that will be used as part of the automatic code testing system, run the `tests.bash` script:

```
cd ~/ros
tests.bash
```

All of the automated tests should run automatically, and if everything is working correctly, the result should show no test failures.

### Step 5: Commit and Push Changes for an Official Submission
Once you verify that the automated tests pass on your local machine, you should be ready to push the changes to GitHub for official grading.

Using GitKraken or the command line, follow the first lecture video from September 4th, 2021.

- Stage all changes
- Commit all changes to the master branch with a message containing the word "official"
- Push to GitHub

After doing this, you should get an email about a pull request getting merged. This is confirmation that the official submission was successfully done.
