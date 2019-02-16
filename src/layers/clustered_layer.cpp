#include "layer.hpp"
#include "tbb/tbb.h"

class ClusteredLayer
    : public Layer
{
protected:
    unsigned m_nIn;
    unsigned m_nOut;

    std::vector<synapse_t> m_synapses;
    std::vector<std::vector<synapse_t> > incoming_synapses;
public:
    ClusteredLayer(
        unsigned nIn,
        unsigned nOut,
        const std::vector<synapse_t> &synapses
    )
        : m_nIn(nIn)
        , m_nOut(nOut)
        , m_synapses(synapses)
    {
	std::vector<std::vector<synapse_t> > incoming_synapses(m_nOut, std::vector<synapse_t>());
	for(int i = 0; i < m_synapses.size(); i++) {
		synapse_t curr = m_synapses[i];
		int output_neuron = curr.dst;
		std::vector<synapse_t> synapses_to_output = incoming_synapses[output_neuron];
		synapses_to_output.push_back(curr);
		incoming_synapses[output_neuron] = synapses_to_output;
	}
	this->incoming_synapses = incoming_synapses;	 
    }
    
    const char *name() const
    { return "simple"; }
    
    virtual unsigned input_size() const
    { return m_nIn; }
    
    virtual unsigned output_size() const
    { return m_nOut; }
    
    void execute(
        const int8_t *pIn,  // Values of input neurons in -127..+127
        int8_t *pOut        // Values of output neurons in -127..+127
    ) const
    {        
        std::vector<int32_t>  acc(m_nOut, 0); // Create a working vector
	unsigned synapses_size = m_synapses.size();
	for(int i = 0; i < incoming_synapses.size(); i++){
		std::vector<synapse_t> curr_output_neuron_synapses = incoming_synapses[i];
		for(int j = 0; j < curr_output_neuron_synapses.size(); j++){
			synapse_t curr_synapse = curr_output_neuron_synapses[j];
			int32_t contrib = curr_synapse.weight * pIn[ curr_synapse.src];
           		
            		// Add into acc array with 16 fractional bits
            		acc[ curr_synapse.dst ] += contrib >> (23-16);
	
		}
            	pOut[i] = sigmoid( acc[i] ); // compress with sigmoid
        }
    }
};

LayerPtr CreateClusteredLayer(unsigned nIn, unsigned nOut, const std::vector<synapse_t> &synapses)
{
    return std::make_shared<ClusteredLayer>(nIn, nOut, synapses);
}