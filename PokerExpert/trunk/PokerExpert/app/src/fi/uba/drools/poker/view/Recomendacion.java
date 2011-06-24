/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Recomendacion.java
 *
 * Created on 24/06/2011, 03:52:16
 */
package fi.uba.drools.poker.view;

import java.awt.Color;
import java.awt.Font;
import java.awt.Label;

import javax.swing.JComponent;

/**
 *
 * @author Federico
 */
public class Recomendacion extends javax.swing.JFrame {
    static Principal princi;
    static Recomendacion esto;
	private PanelPrincipal panelPrincipal;

    /** Creates new form Recomendacion */
    public Recomendacion(String recomendacion,Principal principal) {
        princi = principal;
        initComponents();
        areaRecomendacion.append(recomendacion);
        this.setResizable(false);
    }
    
        public Recomendacion(String recomendacion) {
        initComponents();
        areaRecomendacion.append(recomendacion);
        this.setResizable(false);
    }
    
        public Recomendacion() {
        initComponents();
        this.setResizable(false);
    }
        


        private void cargarEstilo(JComponent component){
        	component.setBackground(Color.decode("#ffffff"));
        	component.setFont(new java.awt.Font("Serif", Font.BOLD | Font.ITALIC, 14));
            
        }
        private void cargarEstiloLabel(Label component){
        	component.setBackground(Color.decode("#ffffff"));
        	component.setFont(new java.awt.Font("Serif", Font.BOLD | Font.ITALIC, 14));
        }
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        label1 = new java.awt.Label();
        cargarEstiloLabel(label1);
        jScrollPane1 = new javax.swing.JScrollPane();
        cargarEstilo(jScrollPane1);
        areaRecomendacion = new javax.swing.JTextArea();
        cargarEstilo(areaRecomendacion);
        label2 = new java.awt.Label();
        cargarEstiloLabel(label2);
        botonRetirar = new javax.swing.JButton();
        cargarEstilo(botonRetirar);
        botonAumento = new javax.swing.JButton();
        cargarEstilo(botonAumento);
        botonPaso = new javax.swing.JButton();
        cargarEstilo(botonPaso);
        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Recomendacion");
        setAlwaysOnTop(true);

        label1.setText("Recomendacion del sistema experto");

        areaRecomendacion.setColumns(20);
        areaRecomendacion.setEditable(false);
        areaRecomendacion.setRows(5);
        jScrollPane1.setViewportView(areaRecomendacion);

        label2.setText("Que hizo el oponente?");

        botonRetirar.setText("Se retiro o me retire");
        botonRetirar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                botonRetirarActionPerformed(evt);
            }
        });

        botonAumento.setText("Aumento");
        botonAumento.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                botonAumentoActionPerformed(evt);
            }
        });

        botonPaso.setText("Paso");
        botonPaso.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                botonPasoActionPerformed(evt);
            }
        });
        this.panelPrincipal= new PanelPrincipal();
        this.getContentPane().add(this.panelPrincipal);
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this.panelPrincipal);
        this.panelPrincipal.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(40, 40, 40)
                        .addComponent(label1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(18, 18, 18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                    .addComponent(botonRetirar)
                                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(botonAumento, javax.swing.GroupLayout.PREFERRED_SIZE, 109, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(botonPaso, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                .addComponent(jScrollPane1, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.PREFERRED_SIZE, 364, javax.swing.GroupLayout.PREFERRED_SIZE)))))
                .addContainerGap(18, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(18, 18, 18)
                .addComponent(label1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 172, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(label2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(botonRetirar)
                    .addComponent(botonPaso)
                    .addComponent(botonAumento))
                .addContainerGap(17, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    
    
    private void botonAumentoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_botonAumentoActionPerformed
        new Aumento().setVisible(true);
        this.setVisible(false);
    }//GEN-LAST:event_botonAumentoActionPerformed

    private void botonRetirarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_botonRetirarActionPerformed
        this.reset();
        return;
    }//GEN-LAST:event_botonRetirarActionPerformed

    public static Recomendacion getRecomendacion (){
        return esto;
    }
    
    public void reset (){
        this.princi.reset();
        this.setVisible(false);
    }
    private void botonPasoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_botonPasoActionPerformed
        this.reset();
        return;
    }//GEN-LAST:event_botonPasoActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {

            public void run() {
                new Recomendacion().setVisible(true);
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextArea areaRecomendacion;
    private javax.swing.JButton botonAumento;
    private javax.swing.JButton botonPaso;
    private javax.swing.JButton botonRetirar;
    private javax.swing.JScrollPane jScrollPane1;
    private java.awt.Label label1;
    private java.awt.Label label2;
    // End of variables declaration//GEN-END:variables
}
