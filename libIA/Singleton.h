#pragma once
// from http://stackoverflow.com/questions/270947/can-any-one-provide-me-a-sample-of-singleton-in-c/271104#271104


class Singleton
{
    public:
        static Singleton& getInstance()
        {
            static Singleton instance;
            return instance;
        }
    private:
        Singleton() {}
        Singleton(Singleton const&);		// Don't Implement.
        void operator=(Singleton const&);	// Don't implement
 };
 
