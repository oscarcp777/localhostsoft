package view;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JTextArea;
import javax.swing.SpinnerModel;
import javax.swing.SpinnerNumberModel;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.border.Border;

import ar.fi.uba.cim2.model.Application;
import ar.fi.uba.cim2.model.Configuracion;
import ar.fi.uba.cim2.view.CheckListFuentes;
import ar.fi.uba.cim2.view.CheckListSumideros;
import ar.fi.uba.cim2.view.HtmlDisponibilidad;
import ar.fi.uba.cim2.view.HtmlEstadisticas;
import ch.randelshofer.quaqua.QuaquaManager;


public class Automatizacion extends JFrame {
	
	private JLabel labelRioValor;
	private JLabel labelCisternaValor;
	private JLabel labelRiegoValor;
	JLabel  theLabel;
	JLabel  theLabel2;
	JLabel tuberia1Label;
	JLabel tuberia2Label;
	JLabel tuberia3Label;
	 JFrame  monitor;
	public JLabel getLabelRioValor() {
		return labelRioValor;
	}

	public void setLabelRioValor(JLabel labelRioValor) {
		this.labelRioValor = labelRioValor;
	}

	public JLabel getLabelCisternaValor() {
		return labelCisternaValor;
	}

	public void setLabelCisternaValor(JLabel labelCisternaValor) {
		this.labelCisternaValor = labelCisternaValor;
	}

	public JLabel getLabelRiegoValor() {
		return labelRiegoValor;
	}

	public void setLabelRiegoValor(JLabel labelRiegoValor) {
		this.labelRiegoValor = labelRiegoValor;
	}

	public JFrame getMonitor() {
		return monitor;
	}

	public void setMonitor(JFrame monitor) {
		this.monitor = monitor;
	}

	public JFrame getConfiguracion() {
		return configuracion;
	}

	public void setConfiguracion(JFrame configuracion) {
		this.configuracion = configuracion;
	}

	public JFrame getDisponibilidad() {
		return disponibilidad;
	}

	public void setDisponibilidad(JFrame disponibilidad) {
		this.disponibilidad = disponibilidad;
	}

	public JFrame getEstadisticas() {
		return estadisticas;
	}

	public void setEstadisticas(JFrame estadisticas) {
		this.estadisticas = estadisticas;
	}

	public JLabel getTuberia1Label() {
		return tuberia1Label;
	}

	public void setTuberia1Label(JLabel tuberia1Label) {
		this.tuberia1Label = tuberia1Label;
	}

	public JLabel getTuberia2Label() {
		return tuberia2Label;
	}

	public void setTuberia2Label(JLabel tuberia2Label) {
		this.tuberia2Label = tuberia2Label;
	}

	public JLabel getTuberia3Label() {
		return tuberia3Label;
	}

	public void setTuberia3Label(JLabel tuberia3Label) {
		this.tuberia3Label = tuberia3Label;
	}

	public JLabel getTheLabel2() {
		return theLabel2;
	}

	public void setTheLabel2(JLabel theLabel2) {
		this.theLabel2 = theLabel2;
	}

	public JLabel getTheLabel() {
		return theLabel;
	}

	public void setTheLabel(JLabel theLabel) {
		this.theLabel = theLabel;
	}
	private JFrame configuracion;
	JFrame disponibilidad;
	JFrame estadisticas;
	public Automatizacion() {
		inicializar();
	}

	public static void main(String args[]) {
		java.awt.EventQueue.invokeLater(new Runnable() {
			public void run() {
				 try { 
			         // set system properties here that affect Quaqua
			         // for example the default layout policy for tabbed
			         // panes:
			             QuaquaManager.setProperty(
			                "Quaqua.tabLayoutPolicy","wrap"
			             );
			         // configure the class loader of the UIManager.
			             UIManager.put(
			                 "ClassLoader", getClass().getClassLoader()
			             );
			         // set the Quaqua Look and Feel in the UIManager.
			             UIManager.setLookAndFeel(
			                 ch.randelshofer.quaqua.QuaquaManager.getLookAndFeel()
			             );
			         } catch (Exception e) {
			             // take an appropriate action here
			         } 
				
				
				
				
				new Automatizacion().setVisible(true);
			}
		});
	}
	
	private  void createMonitor() {
        //Create and set up the window.
        monitor = new JFrame("Proceso de Filtrado");
        monitor.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new ProgressMonitorDemo();
        newContentPane.setOpaque(true); //content panes must be opaque
        monitor.setContentPane(newContentPane);
        
        //Display the window.
        monitor.pack();
        monitor.setSize(350, 650);
        monitor.setVisible(false);
    }
	private  void createDisponibilidad() {
        //Create and set up the window.
         disponibilidad = new JFrame("Disponibilidad");
         disponibilidad.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
 
        //Add content to the window.
         disponibilidad.add(new HtmlDisponibilidad());
 
        //Display the window.
         disponibilidad.pack();
         disponibilidad.setVisible(false);
    }
	private  void createEstadisticas() {
        //Create and set up the window.
         estadisticas = new JFrame("Disponibilidad");
         estadisticas.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
 
        //Add content to the window.
         estadisticas.add(new HtmlEstadisticas());
 
        //Display the window.
         estadisticas.pack();
         estadisticas.setVisible(false);
    }
	private void inicializar() {	
		
		labelRioValor = new JLabel("<html>Valor:  litros<br><br>Maximo:  litros</html>");
		labelCisternaValor = new JLabel("<html>Valor:  litros</html>");
		labelRiegoValor = new JLabel("<html>Valor:  litros<br><br>Minimo:  litros</html>");

		Border rioBorder = BorderFactory.createTitledBorder("Tanque Agua Gris");
		labelRioValor.setBorder(rioBorder);
		Border cisternaBorder = BorderFactory.createTitledBorder("Tanque Agua Gris Filtrada");
		labelCisternaValor.setBorder(cisternaBorder);
		Border riegoBorder = BorderFactory
				.createTitledBorder("Tanque Agua Reciclada");
		labelRiegoValor.setBorder(riegoBorder);
		
		setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
		setTitle("Sistema de Automatizaci—n de Reciclado de Agua Gris ");

		Container content = getContentPane();
		BorderLayout layout = new BorderLayout();
		content.setLayout(layout);
		
		// Panel Configuracion
		JPanel panelConfig = new JPanel();
		Border panelConfigBorder = BorderFactory.createTitledBorder("Panel de Cortrol");
		panelConfig.setBorder(panelConfigBorder);
		panelConfig.setLayout(new GridLayout(5, 1));
		
		JButton fuentesActivas = new JButton();
		fuentesActivas.setText("<html><h1 style='font-size:23px;color:#1d1f21;'>Fuentes</h1></html>");
		fuentesActivas.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				configButtonActionFuentes(evt);
			}
		});
		
		JButton fuentesInactivas = new JButton();
		fuentesInactivas.setText("<html><h1 style='font-size:23px;color:#1d1f21;'>Sumideros</h1></html>");
		fuentesInactivas.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				configButtonActionSumideros(evt);
			}
		});
		
		JButton disponiblidad = new JButton();
		disponiblidad.setText("<html><h1 style='font-size:23px;color:#1d1f21;'>Consultar Disponibilidad</h1></html>");
		disponiblidad.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				consultarDisponibilidadActionPerformed(evt);
			}
		});
		JButton parametros = new JButton();
		parametros.setText("<html><h1 style='font-size:23px;color:#1d1f21;'>Modificar Parametros</h1></html>");
		parametros.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				configButtonActionPerformed(evt);
			}
		});
		JButton estadisticas = new JButton();
		estadisticas.setText("<html><h1 style='font-size:23px;color:#1d1f21;'>Mostrar Estadisticas</h1></html>");
		estadisticas.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				estadisticasButtonActionPerformed(evt);
			}
		});
		
		panelConfig.add(fuentesActivas);
		panelConfig.add(fuentesInactivas);
		panelConfig.add(parametros);
		panelConfig.add(estadisticas);
		panelConfig.add(disponiblidad);
		panelConfig.setPreferredSize(new Dimension(350, 600));

	
		content.add(panelConfig, BorderLayout.LINE_START);
		
		// Panel Grafico
		JPanel panelGrafico = new JPanel();
		Border panelGraficoBorder = BorderFactory.createTitledBorder("Proceso");
		panelGrafico.setBorder(panelGraficoBorder);
		panelGrafico.setLayout(new GridLayout(3, 1));
		
		// Grafico Fila 1
		JPanel pnTanquegris= new JPanel();
		JButton rioButton = new JButton();
		rioButton.setIcon(createImageIcon("tanque.jpeg"));
		rioButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				aguaGrisButtonActionPerformed(evt);
			}
		});
		pnTanquegris.add(rioButton);
		
		
		 String initialText = "<html>\n"+ 
	        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
	        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanques de Agua Gris</FONT></th></tr>"+
	        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\"> "+ Application.getInstance().getTanques().getAguaGrisMax() +"Lts</FONT></td></tr>"+
	        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a tratar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getAguaGris() +" Lts</FONT></td></tr>"+
	        		"</table>";
	    theLabel = new JLabel(initialText) {
	            public Dimension getPreferredSize() {
	                return new Dimension(100, 100);
	            }
	            public Dimension getMinimumSize() {
	            	return new Dimension(100, 100);
	            }
	            public Dimension getMaximumSize() {
	            	return new Dimension(100, 100);
	            }
	        };
	        theLabel.setVerticalAlignment(SwingConstants.CENTER);
	        theLabel.setHorizontalAlignment(SwingConstants.CENTER);
	        Application.getInstance().setFrame(this);
	        
		 pnTanquegris.add(theLabel);
		 pnTanquegris.setLayout(new GridLayout(1, 2));
		panelGrafico.add(pnTanquegris);
		
		JPanel panelSisternas = new JPanel();
		JLabel cisternaLabel = new JLabel(createImageIcon("cisterna2.jpg"));
		panelSisternas.add(cisternaLabel);
		initialText = "<html>\n"+ 
        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanque de Filtrado</FONT></th></tr>"+
        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getFiltradoMax() +" Lts</FONT></td></tr>"+
        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a filtrar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getFiltrado() +" Lts</FONT></td></tr>"+
        		"</table>";
		 tuberia1Label = new JLabel(initialText) {
            public Dimension getPreferredSize() {
                return new Dimension(100, 100);
            }
            public Dimension getMinimumSize() {
            	return new Dimension(100, 100);
            }
            public Dimension getMaximumSize() {
            	return new Dimension(100, 100);
            }
        };
        tuberia1Label.setVerticalAlignment(SwingConstants.CENTER);
        tuberia1Label.setHorizontalAlignment(SwingConstants.CENTER);
		panelSisternas.add(tuberia1Label);
		JLabel cisternaLabel1 = new JLabel(createImageIcon("cisterna2.jpg"));
		panelSisternas.add(cisternaLabel1);
		initialText = "<html>\n"+ 
        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanque de Tratamiento</FONT></th></tr>"+
        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratamientoMax() +" Lts</FONT></td></tr>"+
        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a tratar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratamiento() +" Lts</FONT></td></tr>"+
        		"</table>";
		 tuberia2Label = new JLabel(initialText) {
            public Dimension getPreferredSize() {
                return new Dimension(100, 100);
            }
            public Dimension getMinimumSize() {
            	return new Dimension(100, 100);
            }
            public Dimension getMaximumSize() {
            	return new Dimension(100, 100);
            }
        };
        tuberia2Label.setVerticalAlignment(SwingConstants.CENTER);
        tuberia2Label.setHorizontalAlignment(SwingConstants.CENTER);
		panelSisternas.add(tuberia2Label);
		JLabel cisternaLabel2 = new JLabel(createImageIcon("cisterna2.jpg"));
		panelSisternas.add(cisternaLabel2);
		initialText = "<html>\n"+ 
        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanque de Clorificacion</FONT></th></tr>"+
        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getClorificacionMax() +" Lts</FONT></td></tr>"+
        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a Clorificar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getClorificacion() +" Lts</FONT></td></tr>"+
        		"</table>";
		 tuberia3Label = new JLabel(initialText) {
            public Dimension getPreferredSize() {
                return new Dimension(100, 100);
            }
            public Dimension getMinimumSize() {
            	return new Dimension(100, 100);
            }
            public Dimension getMaximumSize() {
            	return new Dimension(100, 100);
            }
        };
        tuberia3Label.setVerticalAlignment(SwingConstants.CENTER);
        tuberia3Label.setHorizontalAlignment(SwingConstants.CENTER);
		panelSisternas.add(tuberia3Label);
		panelSisternas.setLayout(new GridLayout(1, 6));
		panelGrafico.add(panelSisternas);
		JButton riegoButton = new JButton();
		riegoButton.setIcon(createImageIcon("tanque.jpeg"));
		riegoButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				aguaTratadaButtonActionPerformed(evt);
			}
		});
		JPanel pnTanqueTratado= new JPanel();
		panelGrafico.add(pnTanqueTratado);
		
		pnTanqueTratado.add(riegoButton);
		 initialText = "<html>\n"+ 
				   
	        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
	        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanques de Agua Tratada</FONT></th></tr>"+
	        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratadaMax() +" Lts</FONT></td></tr>"+
	        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua Tratada</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratada() +" Lts</FONT></td></tr>"+
	        		"</table>";
	    theLabel2 = new JLabel(initialText) {
	            public Dimension getPreferredSize() {
	                return new Dimension(100, 100);
	            }
	            public Dimension getMinimumSize() {
	            	return new Dimension(100, 100);
	            }
	            public Dimension getMaximumSize() {
	            	return new Dimension(100, 100);
	            }
	        };
	        Application.getInstance().setFrame(this);
	        theLabel2.setVerticalAlignment(SwingConstants.CENTER);
	        theLabel2.setHorizontalAlignment(SwingConstants.CENTER);
	        pnTanqueTratado.add(theLabel2);
	        pnTanqueTratado.setLayout(new GridLayout(1, 2));

		panelGrafico.setPreferredSize(new Dimension(1200, 800));
		content.add(panelGrafico, BorderLayout.CENTER);
		
		crearConfiguracion();
		createMonitor();
		pack();
		setSize(1500, 1000);
		setLocationRelativeTo(null);
		setVisible(true);
		setResizable(true);
	}
	
	
	
	protected void aguaGrisButtonActionPerformed(ActionEvent evt) {
		// TODO Auto-generated method stub
		
	}

	protected void aguaTratadaButtonActionPerformed(ActionEvent evt) {
		// TODO Auto-generated method stub
		
	}

	private ImageIcon createImageIcon(String path) {
		return createImageIcon(path, ""); 
	}

	private ImageIcon createImageIcon(String path, String description) {
		java.net.URL imgURL = getClass().getResource(path);
		if (imgURL != null) {
			return new ImageIcon(imgURL, description);
		} else {
			System.err.println("No se encontro el archivo: " + path);
			return null;
		}
	}
	
		
	private void consultarDisponibilidadActionPerformed(java.awt.event.ActionEvent evt) {
		createDisponibilidad();
		disponibilidad.setLocationRelativeTo(null);
		disponibilidad.setVisible(true);
	}
	
	private void estadisticasButtonActionPerformed(java.awt.event.ActionEvent evt) {
		
		createEstadisticas();
		estadisticas.setLocationRelativeTo(null);
		estadisticas.setVisible(true);
	}
	
	
	
	private void crearConfiguracion() {
		
		configuracion = new JFrame("Configuracion");
		configuracion.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		configuracion.setLayout(new GridLayout(4, 1));
		
		SpinnerModel toModel = new SpinnerNumberModel(1, 0, 100, 1);
		SpinnerModel riegoModel = new SpinnerNumberModel(0.3, 0.0, 1, 0.1);
		SpinnerModel pcModel = new SpinnerNumberModel(0.3, 0.0, 1, 0.1);
		SpinnerModel rioModel = new SpinnerNumberModel(1, 0, 100, 1);
		SpinnerModel model = new SpinnerNumberModel(1, 0, 100, 1);
		SpinnerModel model2 = new SpinnerNumberModel(500,0, 10000, 50);
		JSpinner tiempoFiltrado = new JSpinner(model);
		JSpinner revolucionAgitado = new JSpinner(model2);
		JSpinner tiempoManteniento = new JSpinner(rioModel);
		JSpinner proporcioEvacuacion = new JSpinner(riegoModel);
		JSpinner tiempoExposicionUV = new JSpinner(toModel);
		JSpinner porcentajeCLoro = new JSpinner(pcModel);
		Configuracion conf =new Configuracion();
		conf.setTiempoFiltradojs(tiempoFiltrado);
		conf.setRevolucionAgitadojs(revolucionAgitado);
		conf.setTiempoMantenientojs(tiempoManteniento);
		conf.setProporcioEvacuacionjs(proporcioEvacuacion);
		conf.setTiempoExposicionUVjs(tiempoExposicionUV);
		conf.setPorccentajeCLorojs(porcentajeCLoro);
		Application.getInstance().setConfiguracion(conf);
		//Filtrado
		JPanel panelRed = new JPanel();
		Border panelRedBorder = BorderFactory.createTitledBorder("Filtrado");
		panelRed.setBorder(panelRedBorder);
		panelRed.setLayout(new GridLayout(5, 3));
		panelRed.add(new JLabel("Tiempo Filtrado: "));
		panelRed.add(tiempoFiltrado);
		panelRed.add(new JLabel(""));
		panelRed.add(new JLabel(""));
		panelRed.add(new JLabel("Revolucion Agitado: "));
		panelRed.add(revolucionAgitado);
		configuracion.add(panelRed);
		
		// Tratamiento biol—gico
		JPanel panelCotas = new JPanel();
		Border panelCotasBorder = BorderFactory.createTitledBorder("Tratamiento biol—gico");
		panelCotas.setBorder(panelCotasBorder);
		panelCotas.setLayout(new GridLayout(5, 2));
		panelCotas.add(new JLabel("Tiempo Manteniento: "));
		panelCotas.add(tiempoManteniento);
		panelCotas.add(new JLabel(""));
		panelCotas.add(new JLabel(""));
		panelCotas.add(new JLabel("Proporcio Evacuacion: "));
		panelCotas.add(proporcioEvacuacion);
		configuracion.add(panelCotas);
		// desinfeccion
		JPanel panelDesinf = new JPanel();
		Border panelDesinfBorder = BorderFactory.createTitledBorder("Desinfecci—n");
		panelDesinf.setBorder(panelDesinfBorder);
		panelDesinf.setLayout(new GridLayout(5, 2));

		panelDesinf.add(new JLabel("Tiempo Exposicion UV: "));
		panelDesinf.add(tiempoExposicionUV);
		panelDesinf.add(new JLabel(""));
		panelDesinf.add(new JLabel(""));
		panelDesinf.add(new JLabel("Porcentaje CLoro: "));
		panelDesinf.add(porcentajeCLoro);
		configuracion.add(panelDesinf);
		
		
		JButton updateButton = new JButton("<html><h1 style='font-size:23px;color:#1d1f21;'>Actualizar</h1></html>");
		updateButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				updateButtonActionPerformed(evt);
			}
		});
		configuracion.add(updateButton);
		configuracion.pack();
		configuracion.setLocationRelativeTo(null);
		configuracion.setVisible(false);
		configuracion.setResizable(false);
	}
	
	private void updateButtonActionPerformed(java.awt.event.ActionEvent evt) {
		Application.getInstance().getConfiguracion().updateParam();
		JOptionPane.showMessageDialog(this,"Se han actualizado los parametros satisfactoriamente");
	}
	
	private void configButtonActionFuentes(java.awt.event.ActionEvent evt) {
		if(Application.getInstance().getCheckListFuentes()==null){
			CheckListFuentes frame = new CheckListFuentes();
			frame.setSize(700,500);
			Application.getInstance().setCheckListFuentes(frame);
		}
		Application.getInstance().getCheckListFuentes().setVisible(true);
	}
	private void configButtonActionSumideros(java.awt.event.ActionEvent evt) {
		if(Application.getInstance().getCheckListSumideros()==null){
			CheckListSumideros frame = new CheckListSumideros();
			frame.setSize(700,500);
			Application.getInstance().setCheckListSumideros(frame);
		}
		Application.getInstance().getCheckListSumideros().setVisible(true);
	}
	private void configButtonActionPerformed(java.awt.event.ActionEvent evt) {
		configuracion.setLocationRelativeTo(null);
		configuracion.setVisible(true);
	}
}
