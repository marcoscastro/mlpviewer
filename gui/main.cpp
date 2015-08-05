#include <gui/gui.h>
#include <stdlib.h>
#include "scaling.h"
#include "NeuralNetwork.h"
#include "EdgeProperties.h"
#include "NodeProperties.h"

class RedesNeuraisFrame: public Frame
{
private:
	NeuralNetwork* neuralNetwork;
	Button * btnAddNeuronio;
	Button * btnAddEntrada;
	Button * btnAddSaida;
	Button * btnAlterar;
	Button * btnConfigurar;
	Button * btnExecutar;
	Button * btnSalvar;
private:
	void onNodeSelected(Object * sender, Node* node, bool selected)
	{
		btnAlterar->setEnabled(selected);
	}
	void onEdgeSelected(Object * sender, Edge* edge, bool selected)
	{
		btnAlterar->setEnabled(selected);
	}	
	void clicked(Object * sender)
	{
		if(sender == btnAddNeuronio)
		{
			neuralNetwork->addNeuron();
			neuralNetwork->grabFocus();
		}
		else if(sender == btnAddEntrada)
		{
			neuralNetwork->addInput();
			neuralNetwork->grabFocus();
		}
		else if(sender == btnAddSaida)
		{
			neuralNetwork->addOutput();
			neuralNetwork->grabFocus();
		}
		else if(sender == btnAlterar)
		{
			if(neuralNetwork->getSelectedNode() != NULL)
				changeNodeProperties(neuralNetwork->getSelectedNode());
			else if(neuralNetwork->getSelectedEdge() != NULL)
				changeEdgeProperties(neuralNetwork->getSelectedEdge());
		}
		else if(sender == btnSalvar)
		{
			neuralNetwork->saveToFile(_T("NeuralNetWork.bin"));
		}
	}
	void changeNodeProperties(Node* node)
	{
		if(!node->is(_T("NeuronNode")))
			return;
		NodePropertyDialog * nodePropertyDialog = new NodePropertyDialog((NeuronNode*)node);
		add(nodePropertyDialog);
		nodePropertyDialog->setClientSize(300, 150);
		nodePropertyDialog->setPosition(NULL);
		nodePropertyDialog->setVisible(true);
		if(nodePropertyDialog->getResultCode() == 1)
			neuralNetwork->notifyDataChanged();
		delete nodePropertyDialog;
	}
	void changeEdgeProperties(Edge* edge)
	{
		EdgePropertyDialog * edgePropertyDialog = new EdgePropertyDialog(edge);
		add(edgePropertyDialog);
		edgePropertyDialog->setClientSize(300, 150);
		edgePropertyDialog->setPosition(NULL);
		edgePropertyDialog->setVisible(true);
		if(edgePropertyDialog->getResultCode() == 1)
			neuralNetwork->notifyDataChanged();
		delete edgePropertyDialog;
	}
public:
	RedesNeuraisFrame(): Frame(_T("Redes Neurais Artificiais"))
	{
		neuralNetwork = new NeuralNetwork();
		neuralNetwork->setOnNodeSelected(this, &RedesNeuraisFrame::onNodeSelected);
		neuralNetwork->setOnEdgeSelected(this, &RedesNeuraisFrame::onEdgeSelected);
		Panel * gpb = new Panel();
		BorderLayout layout;
		layout.add(gpb, BorderLayout::Bottom);
		layout.setMargin(5, 5, 5);
		setLayout(&layout);
		BoxLayout boxLayout(BoxLayout::X_AXIS);
		boxLayout.setMargin(0, 0, 5);
		gpb->setLayout(&boxLayout);
		btnAddNeuronio = new Button(_T("Adicionar Neurônio"));
		gpb->add(btnAddNeuronio);
		btnAddNeuronio->setOnClick(this, &RedesNeuraisFrame::clicked);
		btnAddNeuronio->grabFocus();
		btnAddEntrada = new Button(_T("Adicionar Entrada"));
		btnAddEntrada->setOnClick(this, &RedesNeuraisFrame::clicked);
		gpb->add(btnAddEntrada);
		btnAddSaida = new Button(_T("Adicionar Saída"));
		btnAddSaida->setOnClick(this, &RedesNeuraisFrame::clicked);
		gpb->add(btnAddSaida);
		btnAlterar = new Button(_T("Alterar"));
		btnAlterar->setEnabled(false);
		btnAlterar->setOnClick(this, &RedesNeuraisFrame::clicked);
		gpb->add(btnAlterar);
		btnConfigurar = new Button(_T("Configurar dados"));
		gpb->add(btnConfigurar);
		btnExecutar = new Button(_T("Executar"));
		gpb->add(btnExecutar);
		btnSalvar = new Button(_T("Salvar"));
		gpb->add(btnSalvar);
		btnSalvar->setOnClick(this, &RedesNeuraisFrame::clicked);
		add(neuralNetwork);
		add(gpb);
		setClientSize(800, 600);
		setPosition(NULL);
		try
		{
			neuralNetwork->loadFromFile(_T("NeuralNetWork.bin"));
		}
		catch (const Exception& e)
		{
			Message::warning(_T("Falha na leitura da rede\n") + ConvertFromUtf8(e.what()), _T("Error"));
		}
		setVisible(true);
	}
};


int main(int argc, char *argv[])
{
	try
	{
		RedesNeuraisFrame f;
		return f.getResultCode();
	}
	catch (const Exception& e)
	{
		Message::error(ConvertFromUtf8(e.what()), _T("Error"));
		return 0xFFFF;
	}
}

