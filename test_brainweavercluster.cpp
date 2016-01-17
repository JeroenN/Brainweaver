//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "brainweavercluster.h"

#include <algorithm>
#include <cassert>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "conceptmapcompetency.h"
#include "brainweavercluster.h"
#include "brainweaverclusterfactory.h"
#include "brainweaverhelper.h"
#include "conceptmapconcept.h"
#include "conceptmapexamples.h"
#include "conceptmapexample.h"
#include "conceptmapconceptfactory.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

#ifndef NDEBUG
void ribi::pvdb::Cluster::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    TestHelperFunctions();
    ClusterFactory();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Test operator== and operator!=
  {
    const auto tmp_tests_1 = ClusterFactory().GetTests();
    const int sz = static_cast<int>(tmp_tests_1.size());
    for (int i=0; i!=sz; ++i)
    {
      const auto tmp_tests_a = ClusterFactory().GetTests(); //For crosscompiler
      const boost::shared_ptr<const Cluster> a = tmp_tests_a.at(i);
      if (!a) continue;
      assert(a);
      const auto tmp_tests_b = ClusterFactory().GetTests(); //For crosscompiler
      const boost::shared_ptr<Cluster> b = tmp_tests_b.at(i);
      if (!b) continue;
      assert(a); assert(b);
      assert(operator==(*a,*a));
      assert(operator==(*a,*b));
      assert(operator==(*b,*a));
      assert(operator==(*b,*b));
      for (int j=0; j!=sz; ++j)
      {
        const auto tmp_tests_c = ClusterFactory().GetTests(); //For crosscompiler
        const auto tmp_tests_d = ClusterFactory().GetTests(); //For crosscompiler
        const boost::shared_ptr<const Cluster> c = tmp_tests_c.at(j);
        if (!c) continue;
        assert(c);
        const boost::shared_ptr<Cluster> d = tmp_tests_d.at(j);
        if (!d) continue;
        assert(c); assert(d);
        assert(operator==(*c,*c));
        assert(operator==(*c,*d));
        assert(operator==(*d,*c));
        assert(operator==(*d,*d));
        if (i==j)
        {
          assert(operator==(*a,*c)); assert(operator==(*a,*d));
          assert(operator==(*b,*c)); assert(operator==(*b,*d));
          assert(operator==(*c,*a)); assert(operator==(*c,*b));
          assert(operator==(*d,*a)); assert(operator==(*d,*b));
        }
        else
        {
          assert(!operator==(*a,*c)); assert(!operator==(*a,*d));
          assert(!operator==(*b,*c)); assert(!operator==(*b,*d));
          assert(!operator==(*c,*a)); assert(!operator==(*c,*b));
          assert(!operator==(*d,*a)); assert(!operator==(*d,*b));
        }
      }
    }
  }
  //Test all Clusters with each combination of Concepts
  {
    const std::vector<std::vector<ribi::cmap::Concept> > v
      = GetCombinations(cmap::ConceptFactory().GetTests());
    std::for_each(v.begin(),v.end(),
      [](const std::vector<ribi::cmap::Concept>& concepts)
      {
        const boost::shared_ptr<Cluster> c(new Cluster(concepts));
        assert(c);
        const std::string s = ToXml(*c);
        const auto d = FromXml(s);
        assert(d);
        assert(c != d);
        assert(*c == *d);
      }
    );
  }
}
#endif