package ar.fi.uba.cim2.view;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextPane;
import javax.swing.ListModel;
import javax.swing.ListSelectionModel;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;

import ar.fi.uba.cim2.model.Application;
import ar.fi.uba.cim2.model.Fuente;
import ar.fi.uba.cim2.model.Tanques;

/**
 * @version 1.0 04/24/99
 */
public class CheckListSumideros extends JFrame {
	JFrame frame;
	public CheckListSumideros() {
		super("Listado de Sumideros");

		 JLabel label = new JLabel("<html><h1 style='font-size:18px;'>Haga Click en los Sumideros que desea activar</h1></html>");
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
				for (int i = 0; i < n; i++) {
					Fuente item = (Fuente) model.getElementAt(i);
					if (item.isSelected()) {
						textArea.append(item.toString());
						textArea.append(", Consumo:"+item.getCapacidad()+" Lts");
						textArea.append(System.getProperty("line.separator"));
						total+=item.getCapacidad();
					}
				}
				textArea.append(System.getProperty("line.separator"));
				textArea.append("Consumo Total : "+total);
			}
		});
		JButton clearButton = new JButton("Utilizar Agua Tratada");
		 frame=this;
		clearButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				 Tanques tq=Application.getInstance().getTanques();
				 Application.getInstance().getEstadisticas().setTratada(tq.getTratada());
        		 tq.setTratada(0.0);
			String	initialText = "<html>\n"+ 
		  				   
	        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
	        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanques de Agua Tratada</FONT></th></tr>"+
	        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratadaMax() +" Lts</FONT></td></tr>"+
	        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua Tratada</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratada() +" Lts</FONT></td></tr>"+
	        		"</table>";
     	    Application.getInstance().getFrame().getTheLabel2().setText(initialText);
     	   
     	   frame.dispose();
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
		items[0] = new Fuente("Sistema Riego Jardin",1000);
		items[1] = new Fuente("Mochila Inodoro 1er Piso-1",100);
		items[2] = new Fuente("Mochila Inodoro 1er Piso-2",100);
		items[3] = new Fuente("Mochila Inodoro Planta Baja",100);
		items[4] = new Fuente("Canilla Patio",300);
		items[5] = new Fuente("Lavarropas",300);
		List<Fuente> fuentes= new ArrayList<Fuente>();
		for (int i = 0; i < items.length; i++) {
			fuentes.add( items[i]);
		}
		Application.getInstance().setFuentes(fuentes);
		return items;
	}





	public static void main(String args[]) {
//		try {
//			UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
//		} catch (Exception evt) {}

		CheckListSumideros frame = new CheckListSumideros();
		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		frame.setSize(700,450);
		frame.setVisible(true);
	}
}





