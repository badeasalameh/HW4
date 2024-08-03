#ifndef HW4_JOB_H
#define HW4_JOB_H

#include <string>

using namespace std;

class Job {
public:
    explicit Job(const char* job);
    virtual ~Job() = default;
    string getJob() const;

private:
    string m_job;
};


#endif //HW4_JOB_H
