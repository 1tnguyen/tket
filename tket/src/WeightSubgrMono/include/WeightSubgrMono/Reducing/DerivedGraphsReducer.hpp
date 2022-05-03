// Copyright 2019-2022 Cambridge Quantum Computing
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include "../GraphTheoretic/DerivedGraphs.hpp"
#include "../GraphTheoretic/DerivedGraphsCalculator.hpp"
#include "ReducerWrapper.hpp"

namespace tket {
namespace WeightedSubgraphMonomorphism {

class DomainsAccessor;

class DerivedGraphsReducer : public ReducerInterface {
 public:
  DerivedGraphsReducer(
      const NeighboursData& pattern_ndata, const NeighboursData& target_ndata);

  virtual bool check(std::pair<VertexWSM, VertexWSM> assignment) override;

  virtual ReductionResult reduce(
      std::pair<VertexWSM, VertexWSM> assignment, DomainsAccessor& accessor,
      std::set<VertexWSM>& work_set) override;

 private:
  DerivedGraphStructs::NeighboursAndCountsStorage m_storage;
  DerivedGraphStructs::SortedCountsStorage m_counts_storage;
  DerivedGraphsCalculator m_calculator;
  DerivedGraphs m_derived_pattern_graphs;
  DerivedGraphs m_derived_target_graphs;

  // We will call this several times with different derived graphs data.
  ReductionResult reduce_with_derived_data(
      const DerivedGraphStructs::NeighboursAndCounts&
          pattern_derived_neighbours_data,
      const DerivedGraphStructs::NeighboursAndCounts&
          target_derived_neighbours_data,
      VertexWSM root_pattern_vertex, DomainsAccessor& accessor,
      std::set<VertexWSM>& work_set);
};

}  // namespace WeightedSubgraphMonomorphism
}  // namespace tket
