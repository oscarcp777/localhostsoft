package view;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.SpinnerModel;
import javax.swing.SpinnerNumberModel;
import javax.swing.UIManager;
import javax.swing.border.Border;

import ar.fi.uba.cim2.model.Application;
import ar.fi.uba.cim2.model.Configuracion;
import ar.fi.uba.cim2.view.CheckListFuentes;
import ar.fi.uba.cim2.view.CheckListSumideros;
import ar.fi.uba.cim2.view.HtmlDisponibilidad;
import ar.fi.uba.cim2.view.HtmlEstadisticas;


public class Automatizacion extends JFrame {
	
	private JLabel labelRioValor;
	private JLabel labelCisternaValor;
	private JLabel labelRiegoValor;
	
	private JFrame configuracion;
	JFrame disponibilidad;
	JFrame estadisticas;
	public Automatizacion() {
		inicializar();
	}

	public static void main(String args[]) {
		java.awt.EventQueue.invokeLater(new Runnable() {
			public void run() {
				 UIManager.put("swing.boldMetal", Boolean.FALSE);
				new Automatizacion().setVisible(true);
			}
		});
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
		Border panelConfigBorder = BorderFactory.createTitledBorder("");
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
		panelConfig.add(disponiblidad);
		panelConfig.add(parametros);
		panelConfig.add(estadisticas);

		panelConfig.setPreferredSize(new Dimension(300, 600));

		JLabel labelInundacion = new JLabel("<html>Estado Inundacion: "+ "<span style=\"color: green;\">Bien</span><html>");
//		panelConfig.add(labelInundacion);
		JLabel labelSequia = new JLabel("<html>Estado Sequia: "+ "<span style=\"color: green;\">Bien</span></html>");
//		panelConfig.add(labelSequia);

		content.add(panelConfig, BorderLayout.LINE_START);
		
		// Panel Grafico
		JPanel panelGrafico = new JPanel();
		Border panelGraficoBorder = BorderFactory.createTitledBorder("Proceso");
		panelGrafico.setBorder(panelGraficoBorder);
		panelGrafico.setLayout(new GridLayout(3, 1));
		
		// Grafico Fila 1
		
		JButton rioButton = new JButton();
		rioButton.setIcon(createImageIcon("tanque.jpeg"));
		rioButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				aguaGrisButtonActionPerformed(evt);
			}
		});
		panelGrafico.add(rioButton);
		
		JPanel panelSisternas = new JPanel();
		JLabel cisternaLabel = new JLabel(createImageIcon("cisterna2.jpg"));
		panelSisternas.add(cisternaLabel);
		JLabel tuberia1Label = new JLabel(createImageIcon("tubo_vacio.jpg"));
		panelSisternas.add(tuberia1Label);
		JLabel cisternaLabel1 = new JLabel(createImageIcon("cisterna2.jpg"));
		panelSisternas.add(cisternaLabel1);
		JLabel tuberia2Label = new JLabel(createImageIcon("tubo_lleno.jpg"));
		panelSisternas.add(tuberia2Label);
		JLabel cisternaLabel2 = new JLabel(createImageIcon("cisterna2.jpg"));
		panelSisternas.add(cisternaLabel2);
		panelSisternas.setLayout(new GridLayout(1, 5));
		panelGrafico.add(panelSisternas);
		JButton riegoButton = new JButton();
		riegoButton.setIcon(createImageIcon("tanque.jpeg"));
		riegoButton.addActionListener(new java.awt.event.ActionListener() {
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				aguaTratadaButtonActionPerformed(evt);
			}
		});
		panelGrafico.add(riegoButton);
		
		

		panelGrafico.setPreferredSize(new Dimension(1200, 800));
		content.add(panelGrafico, BorderLayout.CENTER);
		
		crearConfiguracion();
		createDisponibilidad();
		createEstadisticas();
		pack();
		setSize(1200, 800);
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
		disponibilidad.setLocationRelativeTo(null);
		disponibilidad.setVisible(true);
	}
	
	private void estadisticasButtonActionPerformed(java.awt.event.ActionEvent evt) {
		estadisticas.setLocationRelativeTo(null);
		estadisticas.setVisible(true);
	}
	
	
	
	private void crearConfiguracion() {
		
		configuracion = new JFrame("Configuracion");
		configuracion.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		configuracion.setLayout(new GridLayout(4, 1));
		
		SpinnerModel toModel = new SpinnerNumberModel(500,0, 10000, 100);
		SpinnerModel riegoModel = new SpinnerNumberModel(0.3, 0.0, 1, 0.1);
		SpinnerModel pcModel = new SpinnerNumberModel(0.3, 0.0, 1, 0.1);
		SpinnerModel rioModel = new SpinnerNumberModel(500,0, 10000, 100);
		SpinnerModel model = new SpinnerNumberModel(1, 0, 100, 1);
		SpinnerModel model2 = new SpinnerNumberModel(1, 0, 100, 1);
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
			frame.setSize(700,450);
			Application.getInstance().setCheckListFuentes(frame);
		}
		Application.getInstance().getCheckListFuentes().setVisible(true);
	}
	private void configButtonActionSumideros(java.awt.event.ActionEvent evt) {
		if(Application.getInstance().getCheckListSumideros()==null){
			CheckListSumideros frame = new CheckListSumideros();
			frame.setSize(700,450);
			Application.getInstance().setCheckListSumideros(frame);
		}
		Application.getInstance().getCheckListSumideros().setVisible(true);
	}
	private void configButtonActionPerformed(java.awt.event.ActionEvent evt) {
		configuracion.setLocationRelativeTo(null);
		configuracion.setVisible(true);
	}
}
