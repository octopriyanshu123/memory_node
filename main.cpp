// #include "ros/ros.h"
// #include "std_msgs/String.h"
// #include "std_msgs/Int32.h"
// #include <string>
// #include <type_traits>

// template <typename T>
// class MyTopic {
// public:
//     MyTopic(const std::string& topic_name) : topic_name_(topic_name) {
//         pub_ = nh_.advertise<T>(topic_name_, 10);
//         sub_ = nh_.subscribe(topic_name_, 10, &MyTopic::callback, this);
//         timer_ = nh_.createTimer(ros::Duration(1.0), &MyTopic::timerCallback, this);
//     }

// private:
//     ros::NodeHandle nh_;
//     ros::Publisher pub_;
//     ros::Subscriber sub_;
//     ros::Timer timer_;
//     std::string topic_name_;
//     T msg_data_;

//     void callback(const typename T::ConstPtr& msg) {
//         msg_data_ = *msg;
        
//         if constexpr (std::is_same<T, std_msgs::String>::value) {
//             ROS_INFO("Received: %s", msg_data_.data.c_str());
//         }
//         else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//             ROS_INFO("Received: %d", msg_data_.data);
//         }
//     }

//     void timerCallback(const ros::TimerEvent&) {
//         pub_.publish(msg_data_);

//         if constexpr (std::is_same<T, std_msgs::String>::value) {
//             ROS_INFO("Published: %s", msg_data_.data.c_str());
//         }
//         else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//             ROS_INFO("Published: %d", msg_data_.data);
//         }
//     }
// };

// int main(int argc, char **argv) {
//     ros::init(argc, argv, "memory_node");

//     MyTopic<std_msgs::String> my_topic_string("my_string_topic");
//     MyTopic<std_msgs::Int32> my_topic_int("my_int_topic");

//     ros::spin();
//     return 0;
// }


// #include "ros/ros.h"
// #include "std_msgs/String.h"
// #include "std_msgs/Int32.h"
// #include <string>
// #include <thread>
// #include <atomic>

// template <typename T>
// class MyTopic {
// public:
//     MyTopic(const std::string& topic_name) : topic_name_(topic_name), is_active_(true) {
//         pub_ = nh_.advertise<T>(topic_name_, 10);
//         sub_ = nh_.subscribe(topic_name_, 10, &MyTopic::callback, this);
//         timer_ = nh_.createTimer(ros::Duration(1.0), &MyTopic::timerCallback, this);
//     }

//     void start() {
//         is_active_ = true;
//     }

//     void stop() {
//         is_active_ = false;
//     }

//     bool isActive() const {
//         return is_active_;
//     }

// private:
//     ros::NodeHandle nh_;
//     ros::Publisher pub_;
//     ros::Subscriber sub_;
//     ros::Timer timer_;
//     std::string topic_name_;
//     T msg_data_;
//     std::atomic<bool> is_active_;  

//     void callback(const typename T::ConstPtr& msg) {
//         msg_data_ = *msg;
        
//         if constexpr (std::is_same<T, std_msgs::String>::value) {
//             ROS_INFO("Received: %s", msg_data_.data.c_str());
//         }
//         else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//             ROS_INFO("Received: %d", msg_data_.data);
//         }
//     }

//     void timerCallback(const ros::TimerEvent&) {
//         if (is_active_) {
//             pub_.publish(msg_data_);

//             if constexpr (std::is_same<T, std_msgs::String>::value) {
//                 ROS_INFO("Published: %s", msg_data_.data.c_str());
//             }
//             else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//                 ROS_INFO("Published: %d", msg_data_.data);
//             }
//         }
//     }
// };

// void asyncSpin() {
//     ros::Rate rate(10); 
//     while (ros::ok()) {
//         ros::spinOnce(); 
//         rate.sleep();    
//     }
// }

// int main(int argc, char **argv) {
//     ros::init(argc, argv, "memory_node");

//     MyTopic<std_msgs::String> my_topic_string("my_string_topic");
//     MyTopic<std_msgs::Int32> my_topic_int("my_int_topic");

//     std::thread spinner_thread(asyncSpin);

//     ros::Duration(5.0).sleep();  
//     my_topic_string.start();
//     my_topic_int.start();
//     ROS_INFO("Publisher and Subscriber started.");

//     ros::Duration(5.0).sleep();  
//     my_topic_string.stop();
//     my_topic_int.stop();
//     ROS_INFO("Publisher and Subscriber stopped.");

//     spinner_thread.join(); 

//     return 0;
// }


// #include "ros/ros.h"
// #include "std_msgs/String.h"
// #include "std_msgs/Int32.h"
// #include <string>
// #include <thread>
// #include <atomic>
// #include <std_srvs/Empty.h>

// template <typename T>
// class MyTopic {
// public:
//     MyTopic(const std::string& topic_name) : topic_name_(topic_name), is_active_(false) {
//         pub_ = nh_.advertise<T>(topic_name_, 10);
//         sub_ = nh_.subscribe(topic_name_, 10, &MyTopic::callback, this);
//         timer_ = nh_.createTimer(ros::Duration(1.0), &MyTopic::timerCallback, this);

//         // Service to start and stop the spin
//         start_service_ = nh_.advertiseService("start_spin", &MyTopic::startSpin, this);
//         stop_service_ = nh_.advertiseService("stop_spin", &MyTopic::stopSpin, this);
//     }

//     // Service to start the spin (publish and subscribe)
//     bool startSpin(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
//         is_active_ = true;
//         ROS_INFO("Spin started.");
//         return true;
//     }

//     // Service to stop the spin (publish and subscribe)
//     bool stopSpin(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
//         is_active_ = false;
//         ROS_INFO("Spin stopped.");
//         return true;
//     }

//     // Check if the publisher and subscriber are active
//     bool isActive() const {
//         return is_active_;
//     }

// private:
//     ros::NodeHandle nh_;
//     ros::Publisher pub_;
//     ros::Subscriber sub_;
//     ros::Timer timer_;
//     ros::ServiceServer start_service_;
//     ros::ServiceServer stop_service_;
//     std::string topic_name_;
//     T msg_data_;
//     std::atomic<bool> is_active_;  // For thread-safety

//     void callback(const typename T::ConstPtr& msg) {
//         msg_data_ = *msg;

//         if constexpr (std::is_same<T, std_msgs::String>::value) {
//             ROS_INFO("Received: %s", msg_data_.data.c_str());
//         }
//         else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//             ROS_INFO("Received: %d", msg_data_.data);
//         }
//     }

//     void timerCallback(const ros::TimerEvent&) {
//         if (is_active_) {
//             pub_.publish(msg_data_);

//             if constexpr (std::is_same<T, std_msgs::String>::value) {
//                 ROS_INFO("Published: %s", msg_data_.data.c_str());
//             }
//             else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//                 ROS_INFO("Published: %d", msg_data_.data);
//             }
//         }
//     }
// };

// // Function to handle spinning in a separate thread
// void asyncSpin() {
//     ros::Rate rate(10);  // Spin at 10Hz
//     while (ros::ok()) {
//         ros::spinOnce();  // Process incoming messages
//         rate.sleep();     // Sleep to maintain the rate
//     }
// }

// int main(int argc, char **argv) {
//     ros::init(argc, argv, "memory_node");

//     // Create instances of MyTopic with different message types
//     MyTopic<std_msgs::String> my_topic_string("my_string_topic");
//     MyTopic<std_msgs::Int32> my_topic_int("my_int_topic");

//     // Start an async spinner in a separate thread
//     std::thread spinner_thread(asyncSpin);

//     // Spin to handle services (blocking call for service handling)
//     ros::spin();  // This will handle incoming service requests and other callbacks

//     // Join the spinner thread before exit
//     spinner_thread.join();

//     return 0;
// }


// #include "ros/ros.h"
// #include "std_msgs/String.h"
// #include "std_msgs/Int32.h"
// #include <string>
// #include <thread>
// #include <atomic>
// #include <std_srvs/Empty.h>
// #include <ros/callback_queue.h>

// template <typename T>
// class MyTopic {
// public:
//     MyTopic(const std::string& topic_name) 
//         : topic_name_(topic_name), is_active_(false), callback_queue_() {

//         // Create a custom node handle with a specific callback queue
//         ros::NodeHandle nh;
//         nh.setCallbackQueue(&callback_queue_);
        
//         pub_ = nh.advertise<T>(topic_name_, 10);
//         sub_ = nh.subscribe(topic_name_, 10, &MyTopic::callback, this);

//         timer_ = nh.createTimer(ros::Duration(1.0), &MyTopic::timerCallback, this);

//         // Service to start and stop the spin
//         start_service_ = nh.advertiseService("start_spin", &MyTopic::startSpin, this);
//         stop_service_ = nh.advertiseService("stop_spin", &MyTopic::stopSpin, this);
//     }

//     // Service to start the spin (publish and subscribe)
//     bool startSpin(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
//         is_active_ = true;
//         ROS_INFO("Spin started.");
//         return true;
//     }

//     // Service to stop the spin (publish and subscribe)
//     bool stopSpin(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
//         is_active_ = false;
//         ROS_INFO("Spin stopped.");
//         return true;
//     }

//     // Check if the publisher and subscriber are active
//     bool isActive() const {
//         return is_active_;
//     }

//     // Function to handle spinning in a separate thread
//     void spin() {
//         ros::Rate rate(10);  // Spin at 10Hz
//         while (ros::ok()) {
//             callback_queue_.callAvailable();  // Process the queue
//             rate.sleep();
//         }
//     }

// private:
//     ros::Publisher pub_;
//     ros::Subscriber sub_;
//     ros::Timer timer_;
//     ros::ServiceServer start_service_;
//     ros::ServiceServer stop_service_;
//     std::string topic_name_;
//     T msg_data_;
//     std::atomic<bool> is_active_;  // For thread-safety
//     ros::CallbackQueue callback_queue_;  // Custom callback queue for each topic

//     void callback(const typename T::ConstPtr& msg) {
//         msg_data_ = *msg;

//         if constexpr (std::is_same<T, std_msgs::String>::value) {
//             ROS_INFO("Received: %s", msg_data_.data.c_str());
//         }
//         else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//             ROS_INFO("Received: %d", msg_data_.data);
//         }
//     }

//     void timerCallback(const ros::TimerEvent&) {
//         if (is_active_) {
//             pub_.publish(msg_data_);

//             if constexpr (std::is_same<T, std_msgs::String>::value) {
//                 ROS_INFO("Published: %s", msg_data_.data.c_str());
//             }
//             else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//                 ROS_INFO("Published: %d", msg_data_.data);
//             }
//         }
//     }
// };

// // Generic topicSpin function for any message type
// template <typename T>
// void topicSpin(MyTopic<T>& topic) {
//     topic.spin();
// }

// int main(int argc, char **argv) {
//     ros::init(argc, argv, "memory_node");

//     // Create instances of MyTopic with different message types
//     MyTopic<std_msgs::String> my_topic_string("my_string_topic");
//     MyTopic<std_msgs::Int32> my_topic_int("my_int_topic");

//     // Start a separate thread for each topic to handle the spinning
//     //std::thread string_topic_thread(topicSpin<std_msgs::String>, std::ref(my_topic_string));
//     std::thread int_topic_thread(topicSpin<std_msgs::Int32>, std::ref(my_topic_int));

//     // Spin to handle services (blocking call for service handling)
//     ros::spin();  // This will handle incoming service requests and other callbacks

//     // Join the spinner threads before exit
//     //string_topic_thread.join();
//     int_topic_thread.join();

//     return 0;
// }


// #include "ros/ros.h"
// #include "std_msgs/String.h"
// #include "std_msgs/Int32.h"
// #include <string>
// #include <atomic>
// #include <std_srvs/Empty.h>
// #include <ros/callback_queue.h>

// template <typename T>
// class MyTopic {
// public:
//     MyTopic(const std::string& topic_name) 
//         : topic_name_(topic_name), is_active_(false), callback_queue_() {

//         // Create a custom node handle with a specific callback queue
//         ros::NodeHandle nh;
//         nh.setCallbackQueue(&callback_queue_);
        
//         pub_ = nh.advertise<T>(topic_name_, 10);
//         sub_ = nh.subscribe(topic_name_, 10, &MyTopic::callback, this);

//         timer_ = nh.createTimer(ros::Duration(1.0), &MyTopic::timerCallback, this);

//         // Service to start and stop the spin
//         start_service_ = nh.advertiseService("start_spin", &MyTopic::startSpin, this);
//         stop_service_ = nh.advertiseService("stop_spin", &MyTopic::stopSpin, this);
//     }

//     // Service to start the spin (publish and subscribe)
//     bool startSpin(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
//         is_active_ = true;
//         ROS_INFO("Spin started.");
//         return true;
//     }

//     // Service to stop the spin (publish and subscribe)
//     bool stopSpin(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
//         is_active_ = false;
//         ROS_INFO("Spin stopped.");
//         return true;
//     }

//     // Check if the publisher and subscriber are active
//     bool isActive() const {
//         return is_active_;
//     }

//     // Function to handle spinning in a separate thread
//     void spin() {
//         ros::Rate rate(10);  // Spin at 10Hz
//         while (ros::ok()) {
//             callback_queue_.callAvailable();  // Process the queue
//             rate.sleep();
//         }
//     }

// private:
//     ros::Publisher pub_;
//     ros::Subscriber sub_;
//     ros::Timer timer_;
//     ros::ServiceServer start_service_;
//     ros::ServiceServer stop_service_;
//     std::string topic_name_;
//     T msg_data_;
//     std::atomic<bool> is_active_;  // For thread-safety
//     ros::CallbackQueue callback_queue_;  // Custom callback queue for each topic

//     void callback(const typename T::ConstPtr& msg) {
//         msg_data_ = *msg;

//         if constexpr (std::is_same<T, std_msgs::String>::value) {
//             ROS_INFO("Received: %s", msg_data_.data.c_str());
//         }
//         else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//             ROS_INFO("Received: %d", msg_data_.data);
//         }
//     }

//     void timerCallback(const ros::TimerEvent&) {
//         if (is_active_) {
//             pub_.publish(msg_data_);

//             if constexpr (std::is_same<T, std_msgs::String>::value) {
//                 ROS_INFO("Published: %s", msg_data_.data.c_str());
//             }
//             else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
//                 ROS_INFO("Published: %d", msg_data_.data);
//             }
//         }
//     }
// };

// // Generic topicSpin function for any message type
// template <typename T>
// void topicSpin(MyTopic<T>& topic) {
//     topic.spin();
// }

// int main(int argc, char **argv) {
//     ros::init(argc, argv, "memory_node");

//     // Create instances of MyTopic with different message types
//     MyTopic<std_msgs::String> my_topic_string("my_string_topic");
//     MyTopic<std_msgs::Int32> my_topic_int("my_int_topic");

//     // Spin to handle services (blocking call for service handling)
//     ros::spin();  // This will handle incoming service requests and other callbacks

//     return 0;
// }


#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include <string>
#include <thread>
#include <atomic>
#include <std_srvs/Empty.h>

template <typename T>
class MyTopic {
public:
    MyTopic(const std::string& topic_name) : topic_name_(topic_name), is_active_(false) {
        pub_ = nh_.advertise<T>(topic_name_, 10);
        sub_ = nh_.subscribe(topic_name_, 10, &MyTopic::callback, this);
        timer_ = nh_.createTimer(ros::Duration(1.0), &MyTopic::timerCallback, this);

        // Service to start and stop the spin
        start_service_ = nh_.advertiseService("start_spin", &MyTopic::startSpin, this);
        stop_service_ = nh_.advertiseService("stop_spin", &MyTopic::stopSpin, this);
    }

    // Service to start the spin (publish and subscribe)
    bool startSpin(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
        is_active_ = true;
        ROS_INFO("Spin started.");
        return true;
    }

    // Service to stop the spin (publish and subscribe)
    bool stopSpin(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
        is_active_ = false;
        ROS_INFO("Spin stopped.");
        return true;
    }

    // Check if the publisher and subscriber are active
    bool isActive() const {
        return is_active_;
    }

private:
    ros::NodeHandle nh_;
    ros::Publisher pub_;
    ros::Subscriber sub_;
    ros::Timer timer_;
    ros::ServiceServer start_service_;
    ros::ServiceServer stop_service_;
    std::string topic_name_;
    T msg_data_;
    std::atomic<bool> is_active_;  // For thread-safety

    void callback(const typename T::ConstPtr& msg) {
        msg_data_ = *msg;

        if constexpr (std::is_same<T, std_msgs::String>::value) {
            ROS_INFO("Received: %s", msg_data_.data.c_str());
        }
        else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
            ROS_INFO("Received: %d", msg_data_.data);
        }
    }

    void timerCallback(const ros::TimerEvent&) {
        if (is_active_) {
            pub_.publish(msg_data_);

            if constexpr (std::is_same<T, std_msgs::String>::value) {
                ROS_INFO("Published: %s", msg_data_.data.c_str());
            }
            else if constexpr (std::is_same<T, std_msgs::Int32>::value) {
                ROS_INFO("Published: %d", msg_data_.data);
            }
        }
    }
};

// Function to handle spinning in a separate thread
void asyncSpin() {
    ros::Rate rate(10);  // Spin at 10Hz
    while (ros::ok()) {
        ros::spinOnce();  // Process incoming messages
        rate.sleep();     // Sleep to maintain the rate
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "memory_node");

    // Create instances of MyTopic with different message types
    MyTopic<std_msgs::String> my_topic_string("my_string_topic");
    MyTopic<std_msgs::Int32> my_topic_int("my_int_topic");

    // Start an async spinner in a separate thread
    std::thread spinner_thread(asyncSpin);

    // Spin to handle services (blocking call for service handling)
    ros::spin();  // This will handle incoming service requests and other callbacks

    // Join the spinner thread before exit
    spinner_thread.join();

    return 0;
}
