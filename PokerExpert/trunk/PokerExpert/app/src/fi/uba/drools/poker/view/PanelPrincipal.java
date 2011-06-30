package fi.uba.drools.poker.view;

import java.awt.Graphics;

import javax.swing.ImageIcon;
import javax.swing.JPanel;

import fi.uba.drools.poker.utils.Constants;
/**
 * Clase que hereda de Jpanel utilizada como imagen de fondo del Applet
 * @author ocaceres
 *
 */
public class PanelPrincipal extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public PanelPrincipal() {
		super();
		
	}
	/*
	 * (non-Javadoc)
	 * @see javax.swing.JComponent#paintComponent(java.awt.Graphics)
	 */
	protected void paintComponent(Graphics g) {
		
		ClassLoader cl = this.getClass().getClassLoader();
		ImageIcon imagen =  new ImageIcon(cl.getResource(Constants.IMAGEN_FONDO));
		g.drawImage(imagen.getImage(),0,0,280,540,null);
		setOpaque(false);
		super.paintComponent(g);
    }

}
