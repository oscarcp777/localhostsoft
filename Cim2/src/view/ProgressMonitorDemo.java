/*
 * Copyright (c) 1995, 2008, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *   - Neither the name of Oracle or the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */ 

package view;

import java.awt.BorderLayout;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.Random;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ProgressMonitor;
import javax.swing.SwingWorker;

import ar.fi.uba.cim2.model.Application;
import ar.fi.uba.cim2.model.Estadisticas;
import ar.fi.uba.cim2.model.Tanques;

public class ProgressMonitorDemo extends JPanel
                                 implements ActionListener,
                                            PropertyChangeListener {

    private ProgressMonitor progressMonitor;
    private JButton startButton;
    private JTextArea taskOutput;
    private Task task;

    class Task extends SwingWorker<Void, Void> {
        @Override
        public Void doInBackground() {
            Random random = new Random();
            int progress = 0;
            setProgress(0);
            try {
                Thread.sleep(1000);
                while (progress < 100 && !isCancelled()) {
                    //Sleep for up to one second.
                    Thread.sleep(random.nextInt(1000));
                    //Make random progress.
                    progress += random.nextInt(10);
                    setProgress(Math.min(progress, 100));
                }
            } catch (InterruptedException ignore) {}
            return null;
        }

        @Override
        public void done() {
        	Estadisticas et= Application.getInstance().getEstadisticas();
        	Toolkit.getDefaultToolkit().beep();
        	startButton.setEnabled(true);
        	String initialText="";
        	progressMonitor.setProgress(100);
        	if(Application.getInstance().getNumeroProceso().equals(Integer.valueOf(1))){
        		startButton.setText("<html><h1 style='font-size:15px;color:#1d1f21;'>Empezar Proceso de Tratamiento Biologico</h1></html>");
        		Application.getInstance().incrementarProceso();
        	}else if(Application.getInstance().getNumeroProceso().equals(Integer.valueOf(2))){
        		startButton.setText("<html><h1 style='font-size:15px;color:#1d1f21;'>Empezar Proceso de Clorificacion</h1></html>");
        		Application.getInstance().incrementarProceso();
        	}else if(Application.getInstance().getNumeroProceso().equals(Integer.valueOf(3))){
        		startButton.setText("<html><h1 style='font-size:15px;color:#1d1f21;'>Proceso terminado exitosamente</h1></html>");
        		startButton.setEnabled(false);
        
        		 Tanques tq=Application.getInstance().getTanques();
        		
        		 tq.setTratada(tq.getClorificacion());
        		 et.setTratada(et.getTratada()+tq.getClorificacion());
        		 tq.setClorificacion(0.0);
        		 tq.setCloro(tq.getCloro()-(tq.getCloro()*Application.getInstance().getConfiguracion().getPorccentajeCLoro()));
        		 et.setCloro(tq.getCloro());
        		 initialText = "<html>\n"+ 
     	        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
     	        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanque de Clorificacion</FONT></th></tr>"+
     	        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getClorificacionMax() +" Lts</FONT></td></tr>"+
     	        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a Clorificar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getClorificacion() +" Lts</FONT></td></tr>"+
     	        		"</table>";
     	      Application.getInstance().getFrame().getTuberia3Label().setText(initialText);
     	      
     	     initialText = "<html>\n"+ 
  				   
	        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
	        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanques de Agua Tratada</FONT></th></tr>"+
	        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratadaMax() +" Lts</FONT></td></tr>"+
	        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua Tratada</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratada() +" Lts</FONT></td></tr>"+
	        		"</table>";
     	    Application.getInstance().getFrame().getTheLabel2().setText(initialText);
   		 taskOutput.append("El proceso de tratamiento de Agua gris se ha realizado exitosamente \n Obteniendose: "+Application.getInstance().getTanques().getTratada()+" Lts de Agua Tratada \n\n\n");
        	}
        }
    }

    public ProgressMonitorDemo() {
        super(new BorderLayout());

        //Create the demo's UI.
        startButton = new JButton("<html><h1 style='font-size:15px;color:#1d1f21;'>Empezar Proceso de Filtrado</h1></html>");
        startButton.setActionCommand("start");
        startButton.addActionListener(this);
        taskOutput = new JTextArea(5, 20);
        taskOutput.setMargin(new Insets(5,5,5,5));
        taskOutput.setEditable(false);

        add(startButton, BorderLayout.PAGE_START);
        add(new JScrollPane(taskOutput), BorderLayout.CENTER);
        setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

    }


    /**
     * Invoked when the user presses the start button.
     */
    public void actionPerformed(ActionEvent evt) {
    	Estadisticas et= Application.getInstance().getEstadisticas();
    	String message="";
    	String initialText="";
    	if(Application.getInstance().getNumeroProceso().equals(Integer.valueOf(1))){
    		message="Ejecutando el Proceso de Filtrado \n Tiempo Filtrado: "+Application.getInstance().getConfiguracion().getTiempoFiltrado()+" Horas \n Revoluciones: "+Application.getInstance().getConfiguracion().getRevolucionAgitado()+ " revoluciones /minuto \n";
        progressMonitor = new ProgressMonitor(ProgressMonitorDemo.this,message,"", 0, 100);
        taskOutput.append(message);
        Tanques tq=Application.getInstance().getTanques();
		if(tq.getAguaGris()>tq.getFiltradoMax()){
			tq.setFiltrado(tq.getFiltradoMax());
			tq.setAguaGris(tq.getAguaGris()-tq.getFiltradoMax());
		}else{
			tq.setFiltrado(tq.getAguaGris());
			et.setFiltrado(et.getFiltrado()+tq.getFiltrado());
			tq.setAguaGris(0.0);
		}
		 initialText = "<html>\n"+ 
        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanques de Agua Gris</FONT></th></tr>"+
        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\"> "+ Application.getInstance().getTanques().getAguaGrisMax() +"Lts</FONT></td></tr>"+
        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a tratar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getAguaGris() +" Lts</FONT></td></tr>"+
        		"</table>";
		 Application.getInstance().getFrame().getTheLabel().setText(initialText);
		 initialText = "<html>\n"+ 
	        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
	        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanque de Filtrado</FONT></th></tr>"+
	        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getFiltradoMax() +" Lts</FONT></td></tr>"+
	        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a filtrar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getFiltrado() +" Lts</FONT></td></tr>"+
	        		"</table>";
		 Application.getInstance().getFrame().getTuberia1Label().setText(initialText);
    	}else if(Application.getInstance().getNumeroProceso().equals(Integer.valueOf(2))){
    		  message="Ejecutando el Proceso de Proceso de Tratamiento Biologico \n Tiempo Manteniento: "+Application.getInstance().getConfiguracion().getTiempoManteniento()+" Horas \n Proporcio Evacuacion: "+Application.getInstance().getConfiguracion().getProporcioEvacuacion()+ " % \n";
    	      progressMonitor = new ProgressMonitor(ProgressMonitorDemo.this,message,"", 0, 100);
    	      taskOutput.append(message);
    	      Tanques tq=Application.getInstance().getTanques();
     		 tq.setTratamiento(tq.getFiltrado());
     		 et.setTratamiento(et.getTratamiento()+tq.getTratamiento());
     		 tq.setFiltrado(0.0);
     		initialText = "<html>\n"+ 
 	        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
 	        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanque de Filtrado</FONT></th></tr>"+
 	        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getFiltradoMax() +" Lts</FONT></td></tr>"+
 	        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a filtrar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getFiltrado() +" Lts</FONT></td></tr>"+
 	        		"</table>";
 		 Application.getInstance().getFrame().getTuberia1Label().setText(initialText);
 		 initialText = "<html>\n"+ 
          		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
          		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanque de Tratamiento</FONT></th></tr>"+
          		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratamientoMax() +" Lts</FONT></td></tr>"+
          		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a tratar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratamiento() +" Lts</FONT></td></tr>"+
          		"</table>";
  		Application.getInstance().getFrame().getTuberia2Label().setText(initialText);
    	      
    	}else if(Application.getInstance().getNumeroProceso().equals(Integer.valueOf(3))){
    		  message="Ejecutando el Proceso de Clorificacion \n Tiempo Exposicion UV: "+Application.getInstance().getConfiguracion().getTiempoFiltrado()+" Horas \n Porcentaje CLoro: "+Application.getInstance().getConfiguracion().getRevolucionAgitado()+ " % \n";
    	      progressMonitor = new ProgressMonitor(ProgressMonitorDemo.this,message,"", 0, 100);
    	      taskOutput.append(message);	
    	      Tanques tq=Application.getInstance().getTanques();
    	      et.setDescartada(tq.getTratamiento()*Application.getInstance().getConfiguracion().getProporcioEvacuacion());
    	      Double clo=tq.getTratamiento()-(tq.getTratamiento()*Application.getInstance().getConfiguracion().getProporcioEvacuacion());
      		 tq.setClorificacion(clo);
      		
      		 et.setClorificacion(et.getClorificacion()+tq.getClorificacion());
      		 tq.setTratamiento(0.0);
    	      initialText = "<html>\n"+ 
    	          		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
    	          		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanque de Tratamiento</FONT></th></tr>"+
    	          		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratamientoMax() +" Lts</FONT></td></tr>"+
    	          		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a tratar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getTratamiento() +" Lts</FONT></td></tr>"+
    	          		"</table>";
    	      Application.getInstance().getFrame().getTuberia2Label().setText(initialText);
    	      initialText = "<html>\n"+ 
    	        		"<TABLE BGCOLOR=\"#1d1f21\" BORDER=\"1\" CELLPADDING=\"7\" CELLSPACING=\"0\">"+
    	        		"<tr BGCOLOR=\"#cd6a51\"><th colspan=\"2\"><FONT COLOR=\"#ffffff\" SIZE=\"4\" FACE=\"ARIAL\">Tanque de Clorificacion</FONT></th></tr>"+
    	        		"<tr><td ><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Capacidad del Tanque</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getClorificacionMax() +" Lts</FONT></td></tr>"+
    	        		"<tr><td><FONT COLOR=\"#dfc48c\" SIZE=\"4\">Agua a Clorificar</FONT></td><td ALIGN=\"center\"><FONT COLOR=\"#dfc48c\" SIZE=\"4\" FACE=\"ARIAL\">"+ Application.getInstance().getTanques().getClorificacion() +" Lts</FONT></td></tr>"+
    	        		"</table>";
    	      Application.getInstance().getFrame().getTuberia3Label().setText(initialText);
    	  		
    	}
    		
        
        progressMonitor.setProgress(0);
        task = new Task();
        task.addPropertyChangeListener(this);
        task.execute();
        startButton.setEnabled(false);
    }

    /**
     * Invoked when task's progress property changes.
     */
    public void propertyChange(PropertyChangeEvent evt) {
        if ("progress" == evt.getPropertyName() ) {
            int progress = (Integer) evt.getNewValue();
            progressMonitor.setProgress(progress);
            String message = String.format("Completado %d%%.\n", progress);
            progressMonitor.setNote(message);
            taskOutput.append(message);
            if (progressMonitor.isCanceled() || task.isDone()) {
                Toolkit.getDefaultToolkit().beep();
                if (progressMonitor.isCanceled()) {
                    task.cancel(true);
                    taskOutput.append("Proceso Cancelado.\n");
                } else {
                	if(Application.getInstance().getNumeroProceso().equals(Integer.valueOf(1))){
                		taskOutput.append("Fin Proceso de Filtrado.\n");
                	}else if(Application.getInstance().getNumeroProceso().equals(Integer.valueOf(2))){
                		taskOutput.append("Fin Proceso de Tratamiento Biologico.\n");
                	}else if(Application.getInstance().getNumeroProceso().equals(Integer.valueOf(3))){
                		taskOutput.append("Fin Proceso de Clorificacion.\n");
                	}
                    
                }
                startButton.setEnabled(true);
            }
        }

    }

    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Create and set up the window.
        JFrame frame = new JFrame("Proceso de Filtrado");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JComponent newContentPane = new ProgressMonitorDemo();
        newContentPane.setOpaque(true); //content panes must be opaque
        frame.setContentPane(newContentPane);
        
        //Display the window.
        frame.pack();
        frame.setSize(350, 600);
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }
}
