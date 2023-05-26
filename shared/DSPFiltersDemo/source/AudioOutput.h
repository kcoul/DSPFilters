/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#ifndef DSPDEMO_AUDIOOUTPUT_H
#define DSPDEMO_AUDIOOUTPUT_H

#include "Common.h"
#include "ThreadQueue.h"
#include "FilteringAudioSource.h"

/*
 * Handles Audio Output. Allows insertion of one Dsp::Filter
 * in the output chain, selectable audio source material, and
 * a resampler with dynamically adjustable tempo control.
 *
 */
class AudioOutput
  : private juce::AudioIODeviceCallback
{
public:
  AudioOutput ();
  ~AudioOutput ();

  juce::AudioDeviceManager& getAudioDeviceManager();

  void setGain (float gainDb);
  void setTempo (float tempo);
  void setSource (juce::AudioSource* source);
  void setFilter (Dsp::Filter* filter);
  void setFilterParameters (Dsp::Params parameters);
  void resetFilter ();

protected:
  void doSetGain (float gain);
  void doSetTempo (float tempo);
  void doSetSource (juce::ResamplingAudioSource* source);
  void doSetFilter (Dsp::Filter* filter);
  void doSetFilterParameters (Dsp::Params parameters);
  void doResetFilter ();

  void audioDeviceAboutToStart (juce::AudioIODevice* device) override;

  void audioDeviceIOCallbackWithContext(const float* const* inputChannelData,
      int numInputChannels,
      float* const* outputChannelData,
      int numOutputChannels,
      int numSamples,
      const juce::AudioIODeviceCallbackContext& context) override;

  void audioDeviceStopped() override;

private:
    juce::ScopedPointer<juce::AudioDeviceManager> m_audioDeviceManager;
  ThreadQueue m_queue;
    juce::AudioIODevice* m_device;
    juce::ScopedPointer<FilteringAudioSource> m_filteringAudioSource;
    juce::ResamplingAudioSource* m_resampler;
  float m_gain;
  float m_gainNext;
  float m_tempo;
  float m_tempoNext;
  int m_tempoSamplesFade;
};

#endif
