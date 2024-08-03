#include "Job.h"

Job :: Job(const char *job) : m_job(job)
{}

string Job :: getJob() const
{
    return m_job;
}
