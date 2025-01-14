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

#include "Common.h"
#include "ResamplingReader.h"

ResamplingReader::ResamplingReader (juce::AudioFormatReader* reader)
  : m_reader (reader)
  , m_source (new juce::AudioFormatReaderSource (m_reader, false))
  , m_resampler (new juce::ResamplingAudioSource (m_source, false))
{
  m_source->setLooping (true);
}

ResamplingReader::~ResamplingReader ()
{
}

void ResamplingReader::prepareToPlay (int samplesPerBlockExpected,
                                      double sampleRate)
{
  m_resampler->prepareToPlay (samplesPerBlockExpected, sampleRate);
  m_resampler->setResamplingRatio (m_reader->sampleRate / sampleRate);
}

void ResamplingReader::releaseResources()
{
  m_resampler->releaseResources();
}

void ResamplingReader::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
  m_resampler->getNextAudioBlock (bufferToFill);
}

