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

#ifndef DSPDEMO_MAINPANEL_H
#define DSPDEMO_MAINPANEL_H

#include "Common.h"
#include "ResizableLayout.h"
#include "FilterListener.h"

class MainPanel :
public juce::Component,
public juce::MenuBarModel,
public juce::Button::Listener,
public juce::Slider::Listener,
public juce::ComboBox::Listener,
  public TopLevelResizableLayout,
  public FilterListener
{
public:
  MainPanel();
  ~MainPanel();

  void createCharts (const juce::Rectangle<int>& r);
  void buildFamilyMenu (juce::ComboBox* comboBox);
  void buildTypeMenu (juce::ComboBox* comboBox);

  void paint (juce::Graphics& g);

  void setAudio (int audioId);

  void buttonClicked (juce::Button *ctrl);
  void sliderValueChanged (juce::Slider* ctrl);
  void comboBoxChanged (juce::ComboBox* ctrl);

  void onFilterParameters ();

  juce::StringArray getMenuBarNames();
  juce::PopupMenu getMenuForIndex (int topLevelMenuIndex, const juce::String& menuName);
  void menuItemSelected (int menuItemID, int topLevelMenuIndex);

private:
  template <class DesignType, class StateType>
  void createFilterDesign (Dsp::Filter** pFilter, Dsp::Filter** pAudioFilter);

  template <class DesignType>
  void createFilterState (Dsp::Filter** pFilter, Dsp::Filter** pAudioFilter);

  void createFilter ();

private:
    juce::ListenerList<FilterListener> m_listeners;
    juce::ComboBox* m_menuFamily;
    juce::ComboBox* m_menuType;
    juce::ComboBox* m_menuAudio;
    juce::ComboBox* m_menuStateType;
    juce::ComboBox* m_menuSmoothing;
    juce::Button* m_resetButton;
    juce::Slider* m_volumeSlider;
    juce::Slider* m_tempoSlider;

  int m_lastTypeId;

    juce::ScopedPointer<Dsp::Filter> m_filter;
};

#endif

