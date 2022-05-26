#include "hzpch.h"
#include "layerStack.h"

namespace Hazel {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_layers) {
			layer->onDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		// Layers are pushed into the first part of the stack
		m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
		m_layerInsertIndex++;
	}
	void LayerStack::PushOverlay(Layer* overlay) {
		// Overlays are pushed into second part of stack
		m_layers.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, layer);
		if (it != m_layers.begin() + m_layerInsertIndex) {
			//Note layer is removed from the stack but is not destroyed
			layer->onDetach();
			m_layers.erase(it);
			m_layerInsertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(m_layers.begin() + m_layerInsertIndex, m_layers.end(), overlay);
		if (it != m_layers.end()) {
			//Note overlay is removed from the stack but is not destroyed
			overlay->onDetach();
			m_layers.erase(it);
		}
	}

}
