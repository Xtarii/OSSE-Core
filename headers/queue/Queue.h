#ifndef OSSE_QUEUE
#define OSSE_QUEUE

#include <mutex>
#include <queue>

namespace OSSE {
    /**
     * Thread safe Queue
     *
     * @tparam T Type of object to store
     */
    template<typename T>
    struct Queue {
        private:
            /**
             * Mutex object
             */
            std::mutex mutex_;

            /**
             * Queue object
             */
            std::queue<T> queue_;



        public:
            /**
             * Pushes object back in queue
             *
             * @param obj Object to push back
             */
            void push(T obj) {
                std::unique_lock<std::mutex> lock(mutex_);
                queue_.push(obj);
            }

            /**
             * Pops object from queue
             *
             * @return Object popped
             */
            T pop() {
                std::unique_lock<std::mutex> lock(mutex_);
                if(queue_.empty()) return nullptr;
                T obj = queue_.front();
                queue_.pop();
                return obj;
            }



            /**
             * Checks if queue is empty
             *
             * @return Queue is empty
             */
            bool empty() {
                std::unique_lock<std::mutex> lock(mutex_);
                return queue_.empty();
            }

    };
}

#endif // OSSE_QUEUE
