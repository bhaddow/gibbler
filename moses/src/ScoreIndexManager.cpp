// $Id$

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <cassert>
#include "ScoreIndexManager.h"
#include "ScoreProducer.h"
#include "ScoreComponentCollection.h" // debugging

void ScoreIndexManager::AddScoreProducer(const ScoreProducer* sp)
{
	// Producers must be inserted in the order they are created
  assert(m_begins.size() == (sp->GetScoreBookkeepingID()));
	m_producers.push_back(sp);
  m_begins.push_back(m_last);
	size_t numScoreCompsProduced = sp->GetNumScoreComponents();
	assert(numScoreCompsProduced > 0);
	m_last += numScoreCompsProduced;
	m_ends.push_back(m_last);
	std::cerr << "AddScoreProducer(" << sp << "): id=" << sp->GetScoreBookkeepingID() << ", new last=" << m_last << std::endl;
}

void ScoreIndexManager::Debug_PrintLabeledScores(std::ostream& os, const ScoreComponentCollection2& scc) const
{
	std::vector<float> weights(scc.m_scores.size(), 1.0f);
	Debug_PrintLabeledWeightedScores(os, scc, weights);
}

static std::string getFormat(float foo) 
{
  char buf[32];
  sprintf(buf, "%.4f", foo);
  return buf;
}

void ScoreIndexManager::Debug_PrintLabeledWeightedScores(std::ostream& os, const ScoreComponentCollection2& scc, const std::vector<float>& weights) const
{
  size_t cur_i = 0;
  size_t cur_scoreType = 0;
  while (cur_i < m_last) {
    bool first = true;
    while (cur_i < m_ends[cur_scoreType]) {
      os << "  " << getFormat(scc.m_scores[cur_i]) << "\t" << getFormat(scc.m_scores[cur_i] * weights[cur_i]) << "\t  " << (cur_i < 10 ? " " : "") << cur_i << " ";
      if (first) {
        os << m_producers[cur_scoreType]->GetScoreProducerDescription()
           << std::endl;
        first = false;
      } else {
        os << "    \"         \"" << std::endl;
      }
      cur_i++;
    }
    cur_scoreType++;
  }
}

std::ostream& operator<<(std::ostream& os, const ScoreIndexManager& sim)
{
	size_t cur_i = 0;
	size_t cur_scoreType = 0;
	while (cur_i < sim.m_last) {
		bool first = true;
		while (cur_i < sim.m_ends[cur_scoreType]) {
			os << "  " << (cur_i < 10 ? " " : "") << cur_i << " ";
			if (first) {
				os << sim.m_producers[cur_scoreType]->GetScoreProducerDescription()
					 << std::endl;
				first = false;
			} else {
				os << "    \"         \"" << std::endl;
			}
			cur_i++;
		}
		cur_scoreType++;
	}
	return os;
}
