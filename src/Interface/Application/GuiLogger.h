/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2015 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#ifndef GUI_LOGGER_H
#define GUI_LOGGER_H

#include <Core/Utils/Singleton.h>
#include <Core/Logging/LoggerFwd.h>
#include <boost/shared_ptr.hpp>
#include <QString>

namespace SCIRun {
namespace Gui {

  class GuiLogger : boost::noncopyable
  {
    CORE_SINGLETON(GuiLogger)
  public:
    void logInfo(const QString& message) const;
    void logError(const QString& message) const;
    void logInfoStd(const std::string& message) const { logInfo(QString::fromStdString(message)); }
    void logErrorStd(const std::string& message) const { logError(QString::fromStdString(message)); }
    static void setInstance(Core::Logging::LoggerHandle logger);
  private:
    GuiLogger();
    static Core::Logging::LoggerHandle loggerImpl_;
  };

}}

#endif
