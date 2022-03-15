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
#include <map>
#include <optional>
#include <utility>

#include "GeneralStructs.hpp"

namespace tket {
namespace WeightedSubgraphMonomorphism {

/** The main object used to search for neighbours of a vertex,
 * check for existing edges, and get edge weights.
 */
class NeighboursData {
 public:
  NeighboursData();

  /** Initialise with a given graph with edge weights. */
  explicit NeighboursData(const GraphEdgeWeights& edges_and_weights);

  /** Initialise with a given graph with edge weights. */
  void initialise(const GraphEdgeWeights& edges_and_weights);

  std::size_t get_number_of_edges() const;

  /** Isolated vertices are ignored (actually, not even ignored; they are
   * simply invisible to this class, since the class only sees edges).
   */
  std::size_t get_number_of_nonisolated_vertices() const;

  /** The number of neighbours of the given vertex.
   * (Returns 0 if a vertex doesn't exist. This class has no way to know
   * if a vertex is a valid isolated vertex, since isolated vertices
   * won't be listed; loop edges are not allowed).
   * @param v A vertex.
   * @return The number of neighbours of v.
   */
  std::size_t get_degree(VertexWSM v) const;

  /** Returns the edge weight for edge (v1,v2), or null if there is no edge
   * between v1, v2. (Which might mean that the vertices don't exist at all;
   * but it cannot detect this, since it does not know isolated vertices).
   * @param v1 First vertex.
   * @param v2 Second vertex.
   * @return The edge weight if it exists, or null if it does not exist.
   */
  std::optional<WeightWSM> get_edge_weight_opt(
      VertexWSM v1, VertexWSM v2) const;

  /** Return all the neighbouring vertices of v, together with
   * the edge weights, sorted by neighbouring vertex.
   * The data is stored within this class, so time O(log (number of V)).
   * @param v A vertex.
   * @return The neighbours of v and edge weights, sorted by vertex number.
   */
  const std::vector<std::pair<VertexWSM, WeightWSM>>&
  get_neighbours_and_weights(VertexWSM v) const;

  /** Compute all vertices occurring in an edge, sorted by vertex number.
   * Time O(V log V), only for one-off constructions.
   */
  std::vector<VertexWSM> get_nonisolated_vertices_expensive() const;

  /** Get the list of vertex degrees of all neighbours of v, sorted in
   * increasing order.
   * Constructed afresh each time, so should not be called repeatedly.
   */
  std::vector<std::size_t> get_sorted_degree_sequence_expensive(
      VertexWSM v) const;

  /** Reconstructs the list of neighbours of v, each time.
   * Thus time O(log V + |Neighbours|).
   * One should prefer get_neighbours_and_weights whenever possible,
   * which is cheap.
   * @param v A vertex.
   * @return The recalculated neighbours of v, sorted by vertex number.
   */
  std::vector<VertexWSM> get_neighbours_expensive(VertexWSM v) const;

 private:
  // KEY: a vertex VALUE: all neighbouring vertices, with the edge weights.
  std::map<VertexWSM, std::vector<std::pair<VertexWSM, WeightWSM>>>
      m_neighbours_and_weights_map;

  std::vector<std::pair<VertexWSM, WeightWSM>> m_empty_data;

  std::size_t m_number_of_edges;
};

}  // namespace WeightedSubgraphMonomorphism
}  // namespace tket
