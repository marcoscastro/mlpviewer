#ifndef _NODEPROPERTIES_H_
#define _NODEPROPERTIES_H_
#include <gui/gui.h>
#include <algorithm>
#include "NeuronNode.h"

class NodePropertyDialog: public Dialog
{
private:
	NeuronNode * node;
	Button * btnCancelar;
	Button * btnSalvar;
	ComboBox* cboFuncao;
protected:
	virtual void keyDown(int key, int state)
	{
		Dialog::keyDown(key, state);
		if(key == Key::Escape)
			close();
	}
	void onKeyDown(Object * sender, int key, int state)
	{
		if(key == 13)
			clicked(btnSalvar);
	}
	void clicked(Object * sender)
	{
		if(sender == btnSalvar)
		{
			int index = cboFuncao->getItems()->getIndexOf(cboFuncao->getSelected());
			node->setFunctionType(index);
			setResultCode(1);
		}
	}
	virtual void created()
	{
		Dialog::created();
		Label* labelPeso = new Label(_T("Função de ativação"));
		cboFuncao = new ComboBox(ComboBox::DropDownList);
		btnSalvar = new Button(_T("Salvar"));
		btnCancelar = new Button(_T("Cancelar"));
		cboFuncao->setOnKeyDown(this, &NodePropertyDialog::onKeyDown);
		add(labelPeso);
		add(cboFuncao);
		add(btnSalvar);
		add(btnCancelar);
		labelPeso->getFont()->setSize(16);
		labelPeso->setSize(100, 20);
		labelPeso->setPosition(10, 20);
		cboFuncao->getFont()->setSize(16);
		cboFuncao->setSize(280, 30);
		cboFuncao->setPosition(10, 50);
		btnCancelar->setPosition(300 - btnCancelar->getWidth() - 10,
			150 - btnCancelar->getHeight() - 10);
		btnCancelar->setOnClick(this, &NodePropertyDialog::clicked);
		btnSalvar->setPosition(300 - btnSalvar->getWidth() - btnCancelar->getWidth() - 10,
			150 - btnCancelar->getHeight() - 10);
		btnSalvar->setOnClick(this, &NodePropertyDialog::clicked);
		cboFuncao->getItems()->add(new StringItem(_T("Linear")));
		cboFuncao->getItems()->add(new StringItem(_T("Degrau")));
		cboFuncao->getItems()->add(new StringItem(_T("Bipolar")));
		cboFuncao->getItems()->add(new StringItem(_T("Logística")));
		cboFuncao->getItems()->add(new StringItem(_T("Hiperbólica")));
		cboFuncao->setSelected(node->getFunctionType());
		cboFuncao->grabFocus();
	}
public:
	NodePropertyDialog(NeuronNode * node): Dialog(_T("Informações da Conexão"))
	{
		this->node = node;
	}
};

#endif /* _NODEPROPERTIES_H_ */