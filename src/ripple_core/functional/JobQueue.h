//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef RIPPLE_CORE_JOBQUEUE_H_INCLUDED
#define RIPPLE_CORE_JOBQUEUE_H_INCLUDED

class JobQueue : public Stoppable
{
protected:
    JobQueue (char const* name, Stoppable& parent);

public:
    static JobQueue* New (Stoppable& parent, Journal journal);

    virtual ~JobQueue () { }

    // VFALCO TODO make convenience functions that allow the caller to not 
    //             have to call bind.
    //
    virtual void addJob (JobType type, const std::string& name, const FUNCTION_TYPE<void (Job&)>& job) = 0;

    // Jobs waiting at this priority
    virtual int getJobCount (JobType t) = 0;

    // Jobs waiting plus running at this priority
    virtual int getJobCountTotal (JobType t) = 0;

    // All waiting jobs at or greater than this priority
    virtual int getJobCountGE (JobType t) = 0;

    // jobs waiting, threads doing
    virtual std::vector< std::pair<JobType, std::pair<int, int> > > getJobCounts () = 0;

    virtual void shutdown () = 0;

    virtual void setThreadCount (int c, bool const standaloneMode) = 0;

    // VFALCO TODO Rename these to newLoadEventMeasurement or something similar
    //             since they create the object.
    //
    virtual LoadEvent::pointer getLoadEvent (JobType t, const std::string& name) = 0;

    // VFALCO TODO Why do we need two versions, one which returns a shared
    //             pointer and the other which returns an autoptr?
    //          
    virtual LoadEvent::autoptr getLoadEventAP (JobType t, const std::string& name) = 0;

    virtual bool isOverloaded () = 0;

    virtual Json::Value getJson (int c = 0) = 0;
};

#endif
