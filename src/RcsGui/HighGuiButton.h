/*******************************************************************************

  Copyright (c) 2017, Honda Research Institute Europe GmbH.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. All advertising materials mentioning features or use of this software
     must display the following acknowledgement: This product includes
     software developed by the Honda Research Institute Europe GmbH.

  4. Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#ifndef HIGHGUIBUTTON_H
#define HIGHGUIBUTTON_H

#include "HighGuiWidget.h"

class QPushButton;

namespace Rcs
{

class HighGuiButton : public HighGuiWidget
{
  Q_OBJECT

public:
  typedef void (*CallbackType)();


public:
  HighGuiButton(const std::string& name);
  ~HighGuiButton();

  static HighGuiButton* create(const std::string& name);

  bool pressed(bool reset = true);

  void registerCallback(CallbackType cb_function);

protected Q_SLOTS:
  virtual void update();
  virtual void buttonClicked();

protected:
  QPushButton* _button;
  typedef std::list<CallbackType> CallbackList;
  CallbackList _cb_functions;
};

}

#endif   // HIGHGUIBUTTON_H
