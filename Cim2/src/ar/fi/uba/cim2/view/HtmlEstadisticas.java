package ar.fi.uba.cim2.view;

import java.awt.Dimension;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
 
public class HtmlEstadisticas extends JPanel  {
    JLabel theLabel;
    JTextArea htmlTextArea;
    Integer aguaGris=0;
    Integer filtrado=0;
    Integer tratamiento=0;
    Integer clorificacion=0;
    Integer tratada=0;
    Integer cloro=0;
    
    public HtmlEstadisticas() {
        setLayout(new BoxLayout(this, BoxLayout.LINE_AXIS));
 
        String initialText = "<html>\n"+ 
        		"<h3 ALIGN=\"center\"><FONT COLOR=\"#000000\" SIZE=\"8\" FACE=\"ARIAL\">Estadisticas de Sensores</FONT></h3><BR><BR>"+
        		"<h3 ALIGN=\"center\"><FONT COLOR=\"#000000\" SIZE=\"6\" FACE=\"ARIAL\">Cantidad de Litros que agua que detecto cada sensor</FONT></h3><BR><BR>"+
        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
        		"<tr BGCOLOR=\"#cd6a51\"><th><FONT COLOR=\"#ffffff\" SIZE=\"6\" FACE=\"ARIAL\">Tanques de Agua</FONT></th><th><FONT COLOR=\"#ffffff\" SIZE=\"6\" FACE=\"ARIAL\">Litros disponibles</FONT></th></tr>"+
        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"6\">Valvula del Tanque de Agua Gris</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"6\" FACE=\"ARIAL\">"+aguaGris+"</FONT></td></tr>"+
        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"6\">Valvula del  Tanque Filtrado</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"6\" FACE=\"ARIAL\">"+filtrado+"</FONT></td></tr>"+
        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"6\">Valvula del Tanque Tratamiento</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"6\" FACE=\"ARIAL\">"+tratamiento+"</FONT></td></tr>"+
        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"6\">Valvula del Tanque Clorificacion</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"6\" FACE=\"ARIAL\">"+clorificacion+"</FONT></td></tr>"+
        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"6\">Valvula del Tanque de Agua Tratada</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"6\" FACE=\"ARIAL\">"+tratada+"</FONT></td></tr>"+
        		"</table>";
 
        htmlTextArea = new JTextArea(500, 500);
        htmlTextArea.setText(initialText);
        theLabel = new JLabel(initialText) {
            public Dimension getPreferredSize() {
                return new Dimension(700, 500);
            }
            public Dimension getMinimumSize() {
                return new Dimension(700, 500);
            }
            public Dimension getMaximumSize() {
                return new Dimension(700,500);
            }
        };
        theLabel.setVerticalAlignment(SwingConstants.CENTER);
        theLabel.setHorizontalAlignment(SwingConstants.CENTER);
 
       
 
        JPanel rightPanel = new JPanel();
        rightPanel.setLayout(new BoxLayout(rightPanel, BoxLayout.PAGE_AXIS));
        rightPanel.setBorder(BorderFactory.createCompoundBorder(
                        BorderFactory.createTitledBorder(""),
                        BorderFactory.createEmptyBorder(10,10,10,10)));
        rightPanel.add(theLabel);
 
        setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
        add(Box.createRigidArea(new Dimension(10,0)));
        add(rightPanel);
    }
 
    
 
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event dispatch thread.
     */
    private static void createAndShowGUI() {
        //Create and set up the window.
        JFrame frame = new JFrame("Disponibilidad");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
 
        //Add content to the window.
        frame.add(new HtmlEstadisticas());
 
        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }
 
    public static void main(String[] args) {
        //Schedule a job for the event dispatch thread:
        //creating and showing this application's GUI.
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                //Turn off metal's use of bold fonts
            UIManager.put("swing.boldMetal", Boolean.FALSE);
            createAndShowGUI();
            }
        });
    }



	public JLabel getTheLabel() {
		return theLabel;
	}



	public void setTheLabel(JLabel theLabel) {
		this.theLabel = theLabel;
	}



	public JTextArea getHtmlTextArea() {
		return htmlTextArea;
	}



	public void setHtmlTextArea(JTextArea htmlTextArea) {
		this.htmlTextArea = htmlTextArea;
	}



	public Integer getAguaGris() {
		return aguaGris;
	}



	public void setAguaGris(Integer aguaGris) {
		this.aguaGris = aguaGris;
	}



	public Integer getFiltrado() {
		return filtrado;
	}



	public void setFiltrado(Integer filtrado) {
		this.filtrado = filtrado;
	}



	public Integer getTratamiento() {
		return tratamiento;
	}



	public void setTratamiento(Integer tratamiento) {
		this.tratamiento = tratamiento;
	}



	public Integer getClorificacion() {
		return clorificacion;
	}



	public void setClorificacion(Integer clorificacion) {
		this.clorificacion = clorificacion;
	}



	public Integer getTratada() {
		return tratada;
	}



	public void setTratada(Integer tratada) {
		this.tratada = tratada;
	}



	public Integer getCloro() {
		return cloro;
	}



	public void setCloro(Integer cloro) {
		this.cloro = cloro;
	}
}
