/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "SingleCapturer.hpp"

#include "frame_helper/FrameHelper.h"

using namespace video_streamer_vlc;

SingleCapturer::SingleCapturer(std::string const& name)
    : SingleCapturerBase(name)
{
}

SingleCapturer::~SingleCapturer()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See SingleCapturer.hpp for more detailed
// documentation about them.

bool SingleCapturer::configureHook()
{
    if (! SingleCapturerBase::configureHook())
        return false;
    
    capturer = new VlcCapture(_uri.value());
    capturer->callbacks.push_back(this);
    capturer->start();

    return true;
}
bool SingleCapturer::startHook()
{
    if (! SingleCapturerBase::startHook())
        return false;
    return true;
}
void SingleCapturer::updateHook()
{
    SingleCapturerBase::updateHook();
    cv::Mat image;
    while(capturer->read(image)) {
        frame_helper::FrameHelper::copyMatToFrame(image,frame);
        frame.time = base::Time::now();
        output.reset(&frame);
        _frame.write(output);
    }
}
void SingleCapturer::errorHook()
{
    SingleCapturerBase::errorHook();
}
void SingleCapturer::stopHook()
{
    SingleCapturerBase::stopHook();
}
void SingleCapturer::cleanupHook()
{
    SingleCapturerBase::cleanupHook();
}
void SingleCapturer::imageCallback(){
    trigger();
}
