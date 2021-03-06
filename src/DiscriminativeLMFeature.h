/***********************************************************************
Moses - factored phrase-based language decoder
Copyright (C) 2010 University of Edinburgh

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************/

#pragma once

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "FeatureFunction.h"
#include "Gibbler.h"

namespace Josiah {

/**
 * Feature based on target bigrams.
 **/
class DiscriminativeLMBigramFeature : public Feature {
  public:
    DiscriminativeLMBigramFeature(Moses::FactorType factorId, const std::string& vocabFile="");
    virtual FeatureFunctionHandle getFunction(const Sample& sample) const;
    
    const Word& bos() const;
    const Word& eos() const;
    const std::set<std::string>& vocab() const;
    Moses::FactorType factorId() const;
    static const std::string ROOTNAME;
    
  private:
    std::set<std::string> m_vocab;
    Moses::FactorType m_factorId;
    Word BOS;
    Word EOS;
};


class DiscriminativeLMBigramFeatureFunction : public FeatureFunction {
    public:
      DiscriminativeLMBigramFeatureFunction(const Sample& sample, const DiscriminativeLMBigramFeature& parent);
        
        /** Update the target words.*/
        virtual void updateTarget();
        
        /** Assign the total score of this feature on the current hypo */
        virtual void assignScore(FVector& scores);
    
        /** Score due to one segment */
        virtual void doSingleUpdate(const TranslationOption* option, const TargetGap& gap, FVector& scores);
        /** Score due to two segments. The left and right refer to the target positions.**/
        virtual void doContiguousPairedUpdate(const TranslationOption* leftOption,const TranslationOption* rightOption, 
                                              const TargetGap& gap, FVector& scores);
        virtual void doDiscontiguousPairedUpdate(const TranslationOption* leftOption,const TranslationOption* rightOption, 
                const TargetGap& leftGap, const TargetGap& rightGap, FVector& scores);
    
        /** Score due to flip. Again, left and right refer to order on the <emph>target</emph> side. */
        virtual void doFlipUpdate(const TranslationOption* leftOption,const TranslationOption* rightOption, 
                                  const TargetGap& leftGap, const TargetGap& rightGap, FVector& scores) ;
        
        
    private:
        void scoreBigram(const Word& word1, const Word& word2, FVector& scores);
        /** Score change due to filling in the gapPhrase in the gap.*/
        void doUpdate(const Phrase& gapPhrase, const TargetGap& gap, FVector& scores);
        std::vector<Word> m_targetWords;
        const DiscriminativeLMBigramFeature m_parent;
        
        
};




}
