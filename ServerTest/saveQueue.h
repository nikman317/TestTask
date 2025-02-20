#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class SaveQueue
{
public:

	T pop()
	{
		std::unique_lock<std::mutex> mlock(mutex_);
		while (queue_.empty())
		{
			cond_.wait(mlock);
		}
		auto item = queue_.front();
		queue_.pop();
		return item;
	}

	void push(const T& item)
	{
		std::unique_lock<std::mutex> mlock(mutex_);
		queue_.push(item);
		mlock.unlock();
		cond_.notify_one();
	}


private:
	std::queue<T> queue_;
	std::mutex mutex_;
	std::condition_variable cond_;
};