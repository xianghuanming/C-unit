#include <iostream>
#include <thread>
#include <future>
#include <chrono>

int get_num()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    std::cout<<"异步任务"<<std::endl;
    int num = 1;
    return num;
}

int main()
{
    //1.关联异步任务    
    std::future<int> ret_future = std::async(std::launch::async,get_num);
    //2.执行其他操作
    std::cout<<"执行其他操作"<<std::endl;
    int ret = ret_future.get();
    std::cout<<"ret:"<<ret<<std::endl;
    return 0;
}

/*
执行其他操作
异步任务
ret:1
*/
