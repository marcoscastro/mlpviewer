#ifndef _EDGEPROPERTIES_H_
#define _EDGEPROPERTIES_H_
#include <gui/gui.h>
#include <algorithm>
#include "Edge.h"

class EdgePropertyDialog: public Dialog
{
private:
	Edge * edge;
	Button * btnCancelar;
	Button * btnSalvar;
	Edit* editPeso;
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
			String str = editPeso->getText();
			std::replace(str.begin(), str.end(), _T(','), _T('.'));
			double weight;
			swscanf(str.c_str(), _T("%lf"), &weight);
			edge->setWeight(weight);
			setResultCode(1);
		}
	}
	virtual void created()
	{
		Dialog::created();
		Label* labelPeso = new Label(_T("Peso"));
		editPeso = new Edit();
		btnSalvar = new Button(_T("Salvar"));
		btnCancelar = new Button(_T("Cancelar"));
		String str = Edge::trimZeroes(formatString(_T("%lf"), edge->getWeight()));
		std::replace(str.begin(), str.end(), _T('.'), _T(','));
		editPeso->setText(str);
		editPeso->setOnKeyDown(this, &EdgePropertyDialog::onKeyDown);
		add(labelPeso);
		add(editPeso);
		add(btnSalvar);
		add(btnCancelar);
		labelPeso->getFont()->setSize(16);
		labelPeso->setSize(100, 20);
		labelPeso->setPosition(10, 20);
		editPeso->getFont()->setSize(16);
		editPeso->setSize(280, 30);
		editPeso->setPosition(10, 50);
		btnCancelar->setPosition(300 - btnCancelar->getWidth() - 10,
			150 - btnCancelar->getHeight() - 10);
		btnCancelar->setOnClick(this, &EdgePropertyDialog::clicked);
		btnSalvar->setPosition(300 - btnSalvar->getWidth() - btnCancelar->getWidth() - 10,
			150 - btnCancelar->getHeight() - 10);
		btnSalvar->setOnClick(this, &EdgePropertyDialog::clicked);
		editPeso->selectAll();
		editPeso->grabFocus();
	}
public:
	EdgePropertyDialog(Edge * edge): Dialog(_T("Informações da Conexão"))
	{
		this->edge = edge;
	}
};

#endif /* _EDGEPROPERTIES_H_ */