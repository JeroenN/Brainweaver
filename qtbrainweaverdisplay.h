//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#ifndef QTBRAINWEAVERDISPLAY_H
#define QTBRAINWEAVERDISPLAY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "brainweaverfwd.h"
#pragma GCC diagnostic pop

struct QTableWidget;

namespace ribi {

namespace pvdb {

///Functions for printing
struct QtDisplay
{
  QtDisplay();

  void DisplayRatedConcepts(const File& file,QTableWidget * const table) const;
  void DisplayExamples(const File& file, QTableWidget * const table) const;
  void DisplayValues(const File& file, QTableWidget * const table) const;
  void DisplayMiscValues(const File& file, QTableWidget * const table) const;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTBRAINWEAVERDISPLAY_H
