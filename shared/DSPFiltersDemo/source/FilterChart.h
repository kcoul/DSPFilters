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

#ifndef DSPDEMO_FILTERCHART_H
#define DSPDEMO_FILTERCHART_H

#include "DspFilters/Filter.h"
#include "FilterListener.h"

/*
 * Provides some common functionality for displayed charts.
 *
 */
class FilterChart
: public juce::Component
  , public FilterListener
{
public:
  FilterChart (FilterListeners& listeners);
  ~FilterChart ();

    void paint (juce::Graphics& g);

  void resized ();

  void onFilterChanged (Dsp::Filter* newFilter);
  void onFilterParameters ();

    virtual const juce::String getName() const;
    virtual void paintContents (juce::Graphics& g) = 0;
  virtual void update () = 0;

    static void drawText (juce::Graphics &g,
                          const juce::Point<int> ptOrigin,
                          const juce::String text,
                        juce::Justification just = juce::Justification::bottomLeft);

private:
  void paintName (juce::Graphics& g);

protected:
  FilterListeners& m_listeners;
  Dsp::Filter* m_filter;
  bool m_isDefined;
    juce::Path m_path;

    juce::Colour m_cBack;
    juce::Colour m_cFrame;
    juce::Colour m_cAxis;
    juce::Colour m_cAxisMinor;
    juce::Colour m_cText;
};

/*
 * Chart which has a frequency axis that can be made logarithmic scale
 *
 */
class FrequencyChart : public FilterChart
{
public:
  FrequencyChart (FilterListeners& listeners);
  ~FrequencyChart ();

  void paintOverChildren (juce::Graphics& g);

  // map x=[0..1] to unit frequency F=[0..1]
  float xToF (float x);
};

#endif

