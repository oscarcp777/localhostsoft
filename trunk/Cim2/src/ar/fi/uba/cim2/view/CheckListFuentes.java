package ar.fi.uba.cim2.view;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTree;
import javax.swing.ListCellRenderer;
import javax.swing.ListModel;
import javax.swing.ListSelectionModel;
import javax.swing.UIManager;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.plaf.ColorUIResource;
import javax.swing.plaf.metal.MetalIconFactory;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeCellRenderer;

import ar.fi.uba.cim2.model.Application;
import ar.fi.uba.cim2.model.Fuente;

/**
 * @version 1.0 04/24/99
 */
public class CheckListFuentes extends JFrame {
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

	public CheckListFuentes() {
		super("Listado de Fuentes");

		 JLabel label = new JLabel("<html><h1 style='font-size:18px;'>Haga Click en las fuentes que desea activar</h1></html>");
		    TitledBorder titled = new TitledBorder("Importante");
		    label.setBorder(titled);
//		    add(label);
		
		final JList list = new JList(createData());
		list.setCellRenderer(new CheckListRenderer());
		list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		list.setBorder(new EmptyBorder(0, 4, 0, 0));
		list.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent e) {
				int index = list.locationToIndex(e.getPoint());
				Fuente item = (Fuente) list.getModel()
						.getElementAt(index);
				item.setSelected(!item.isSelected());
				Rectangle rect = list.getCellBounds(index, index);
				list.repaint(rect);
			}
		});
		JScrollPane sp = new JScrollPane(list);

		final JTextArea textArea = new JTextArea(12, 10);
		JScrollPane textPanel = new JScrollPane(textArea);
		JButton printButton = new JButton("Mostrar Capacidad");
		printButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ListModel model = list.getModel();
				int n = model.getSize();
				int total=0;
				textArea.append(System.getProperty("line.separator"));
				for (int i = 0; i < n; i++) {
					Fuente item = (Fuente) model.getElementAt(i);
					if (item.isSelected()) {
						textArea.append(item.toString());
						textArea.append(", Capacidad: "+item.getCapacidad()+" Lts");
						textArea.append(System.getProperty("line.separator"));
						total+=item.getCapacidad();
					}
				}
				textArea.append(System.getProperty("line.separator"));
				textArea.append("Capacidad Total : "+total);
			}
		});
		JButton clearButton = new JButton("Limpiar");
		clearButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				textArea.setText("");
			}
		});
		JPanel panel = new JPanel(new GridLayout(1, 2));
		panel.add(printButton);
		panel.add(clearButton);
		getContentPane().add(label, BorderLayout.NORTH);
		getContentPane().add(sp, BorderLayout.CENTER);
		getContentPane().add(panel, BorderLayout.EAST);
		getContentPane().add(textPanel, BorderLayout.SOUTH);
	}

	private Fuente[] createData() {
		Fuente[] items = new Fuente[6];
		items[0] = new Fuente("Pileta de Nataci—n",1000);
		items[1] = new Fuente("Ducha 1er Piso-1",500);
		items[2] = new Fuente("Ducha 1er Piso-2",500);
		items[3] = new Fuente("Ducha Planta Baja",500);
		items[4] = new Fuente("Lavavajilla",100);
		items[5] = new Fuente("Lavarropas",300);
		List<Fuente> fuentes= new ArrayList<Fuente>();
		for (int i = 0; i < items.length; i++) {
			fuentes.add( items[i]);
		}
		Application.getInstance().setFuentes(fuentes);
		return items;
	}



	class CheckListRenderer extends CheckRenderer implements ListCellRenderer {
		Icon commonIcon;

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

	public static void main(String args[]) {
//		try {
//			UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
//		} catch (Exception evt) {}

		CheckListFuentes frame = new CheckListFuentes();
		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		frame.setSize(700,450);
		frame.setVisible(true);
	}
}



