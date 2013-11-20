package ar.fi.uba.cim2.view;

import java.awt.Component;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JList;
import javax.swing.ListCellRenderer;
import javax.swing.UIManager;

import ar.fi.uba.cim2.model.Fuente;

class CheckListRenderer extends CheckRenderer implements ListCellRenderer {
Icon commonIcon;
protected ImageIcon createImageIcon(String path,
		String description) {
	java.net.URL imgURL = getClass().getResource(path);
	if (imgURL != null) {
		return new ImageIcon(imgURL, description);
	} else {
		System.err.println("Couldn't find file: " + path);
		return null;
	}
}

public CheckListRenderer() {
	check.setBackground(UIManager.getColor("List.textBackground"));
	label.setForeground(UIManager.getColor("List.textForeground"));
	commonIcon = createImageIcon("fuente.jpg","Fuente Icon");
}

public Component getListCellRendererComponent(JList list, Object value,
		int index, boolean isSelected, boolean hasFocus) {
	setEnabled(list.isEnabled());
	check.setSelected(((Fuente) value).isSelected());
	label.setFont(list.getFont());
	label.setText(value.toString());
	label.setSelected(isSelected);
	label.setFocus(hasFocus);
	Icon icon = ((Fuente) value).getIcon();
	if (icon == null) {
		icon = commonIcon;
	}
	label.setIcon(icon);
	return this;
}
}
