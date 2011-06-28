/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Priciapl.java
 *
 * Created on 24/06/2011, 01:06:04
 */
package fi.uba.drools.poker.view;
import java.awt.Color;
import java.awt.Font;
import java.util.HashMap;

import javax.swing.ImageIcon;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JPanel;

import fi.uba.drools.poker.models.Card;
import fi.uba.drools.poker.utils.ResourceManager;

/**
 *
 * @author Federico
 */
public class Principal extends javax.swing.JFrame {

    private static final long serialVersionUID = 1L;
    
	private Card carta1;
    private Card carta2;
    private HashMap< String, String> mapSuit = new  HashMap<String, String>();
    private JPanel panelPrincipal =null;
    
    /** Creates new form Priciapl */
    public Principal() {
        carta1 = new Card(Card.ACE,Card.HEARTS);
        carta2 = new Card(Card.ACE,Card.HEARTS);
        initComponents();
        updateLabel (carta1,labelImagen1);
        updateLabel (carta2,labelImagen2);
        this.setResizable(false);
    }
    private void cargarEstilo(JComponent component){
    	component.setBackground(Color.decode("#FFFFFF"));
    	component.setForeground(Color.decode("#000000"));
//    	component.setOpaque(false);
//    	component.setFont(new java.awt.Font("Serif", Font.BOLD | Font.ITALIC, 14));
        
    }
    private void cargarEstiloLabel(JLabel component){
//    	component.setBackground(Color.decode("#ffffff"));
    	component.setForeground(Color.decode("#000000"));
    	component.setFont(new java.awt.Font("Serif", Font.BOLD | Font.ITALIC, 14));
    }
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        numero1 = new javax.swing.JComboBox();
        palo1 = new javax.swing.JComboBox();
        numero2 = new javax.swing.JComboBox();
        palo2 = new javax.swing.JComboBox();
        cargarEstilo(numero1);
        cargarEstilo(numero2);
        cargarEstilo(palo1);
        cargarEstilo(palo2);
        luzGrande = new javax.swing.JCheckBox();
        cargarEstilo(luzGrande);
        luzGrande.setOpaque(false);
        labelFichas1 = new JLabel();
        cargarEstiloLabel(labelFichas1);
        labelCartas = new JLabel();
//        labelCartas.setBackground(new Color(0xF5FFFA));
        labelCartas.setFont(new Font("Serif", Font.BOLD | Font.ITALIC, 20));
        labelCartas.setForeground(Color.decode("#000000"));
        labelApostadas1 = new JLabel();
        cargarEstiloLabel(labelApostadas1);
        labelJugador1 = new JLabel();
        labelJugador1.setFont(new Font("Serif", Font.BOLD | Font.ITALIC, 20));
        labelJugador1.setForeground(Color.decode("#000000"));
        jSeparator1 = new javax.swing.JSeparator();
        labelFichas2 = new JLabel();
        cargarEstiloLabel(labelFichas2);
        labelApostadas2 = new JLabel();
        cargarEstiloLabel(labelApostadas2);
        jSeparator2 = new javax.swing.JSeparator();
        labelJugador2 = new JLabel();
        labelJugador2.setFont(new Font("Serif", Font.BOLD | Font.ITALIC, 20));
        labelJugador2.setForeground(Color.decode("#000000"));
        personalidadOponente = new javax.swing.JComboBox();
        cargarEstilo(personalidadOponente);
        buttonRecomendar = new javax.swing.JButton();
        buttonRecomendar.setForeground(Color.decode("#000000"));
        buttonRecomendar.setBackground(Color.decode("#ffffff"));
        
        buttonRecomendar.setFont(new java.awt.Font("Serif", Font.BOLD | Font.ITALIC, 20));

      
        labelImagen1 = new javax.swing.JLabel();
        labelImagen2 = new javax.swing.JLabel();
        fichasJugador = new javax.swing.JSpinner();
        cargarEstilo(fichasJugador);
        valorLuzGrande= new javax.swing.JSpinner();
        cargarEstilo(valorLuzGrande);
        labelvalorLuzGrande= new JLabel();
        labelvalorLuzGrande.setText("Valor Luz Grande: ");
        cargarEstiloLabel(labelvalorLuzGrande);
        cargarEstilo(fichasJugador);
        fichasApostadasJugador = new javax.swing.JSpinner();
        cargarEstilo(fichasApostadasJugador);
        fichasApostadasOponente = new javax.swing.JSpinner();
        cargarEstilo(fichasApostadasOponente);
        fichasOponente = new javax.swing.JSpinner();
        cargarEstilo(fichasOponente);
        jMenuBar1 = new javax.swing.JMenuBar();
//        cargarEstilo(jMenuBar1);
        menuArchivo = new javax.swing.JMenu();
//        cargarEstilo(menuArchivo);
        menuItemReiniciar = new javax.swing.JMenuItem();
//        cargarEstilo(menuItemReiniciar);
        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Sistema Experto");
        setAlwaysOnTop(true);
        setBackground(new java.awt.Color(0, 153, 0));
//        setBounds(new java.awt.Rectangle(0, 150, 0, 0));
        setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));

        numero1.setModel(new javax.swing.DefaultComboBoxModel(new String[] {  "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K" }));
        numero1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                numero1ActionPerformed(evt);
            }
        });
        mapSuit.put("Diamantes","d");
        mapSuit.put("Tr�boles","c");
        mapSuit.put("Corazones","h");
        mapSuit.put( "Picas","s");
        palo1.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Corazones", "Diamantes", "Picas", "Tr�boles" }));
        palo1.addItemListener(new java.awt.event.ItemListener() {
            public void itemStateChanged(java.awt.event.ItemEvent evt) {
                palo1ItemStateChanged(evt);
            }
        });
        palo1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                palo1ActionPerformed(evt);
            }
        });

        numero2.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"  }));
        numero2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                numero2ActionPerformed(evt);
            }
        });

        palo2.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Corazones", "Diamantes", "Picas", "Tr�boles" }));
        palo2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                palo2ActionPerformed(evt);
            }
        });

        luzGrande.setText("Luz Grande");

        labelFichas1.setText("Fichas: ");

        labelCartas.setText("Sistema Experto de Poker");

        labelApostadas1.setText("Apostado: ");

        labelJugador1.setText("Jugador");

        labelFichas2.setText("Fichas: ");

        labelApostadas2.setText("Apostado: ");

        labelJugador2.setText("Oponente");

        personalidadOponente.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Agresivo", "Ajustado" }));

        buttonRecomendar.setText("Recomendar Jugada");
//        buttonRecomendar.addActionListener(new java.awt.event.ActionListener() {
//            public void actionPerformed(java.awt.event.ActionEvent evt) {
//                buttonRecomendarActionPerformed(evt);
//            }
//        });

        labelImagen1.setText("jLabel1");

        labelImagen2.setText("jLabel2");

        menuArchivo.setText("Archivo");

        menuItemReiniciar.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_R, java.awt.event.InputEvent.CTRL_MASK));
        menuItemReiniciar.setText("Reiniciar");
//        menuItemReiniciar.addActionListener(new java.awt.event.ActionListener() {
//            public void actionPerformed(java.awt.event.ActionEvent evt) {
//                menuItemReiniciarActionPerformed(evt);
//            }
//        });
        menuArchivo.add(menuItemReiniciar);

        jMenuBar1.add(menuArchivo);

        setJMenuBar(jMenuBar1);
        this.panelPrincipal= new PanelPrincipal();
        this.getContentPane().add(this.panelPrincipal);
        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this.panelPrincipal);
        this.panelPrincipal.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(labelCartas, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(labelFichas2, javax.swing.GroupLayout.PREFERRED_SIZE, 68, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(105,105,105)
                                .addComponent(fichasApostadasOponente, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addContainerGap(28, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                            .addComponent(jSeparator1, javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                .addComponent(labelJugador2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(personalidadOponente, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addComponent(jSeparator2, javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                .addGap(90,90,90)
                                .addComponent(fichasApostadasJugador, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                .addComponent(labelApostadas2, javax.swing.GroupLayout.PREFERRED_SIZE, 68, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 116, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(labelJugador1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(labelFichas1, javax.swing.GroupLayout.PREFERRED_SIZE, 64, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 21, Short.MAX_VALUE)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                    .addComponent(luzGrande)
                                    .addComponent(fichasJugador, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE))))
                        .addContainerGap(18, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER, false)
                            .addComponent(buttonRecomendar, javax.swing.GroupLayout.Alignment.CENTER, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                .addComponent(labelApostadas1, javax.swing.GroupLayout.PREFERRED_SIZE, 81, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(24,24,24)
                                .addComponent( fichasOponente, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
            .addGroup(layout.createSequentialGroup()
                .addGap(12, 12, 12)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                     .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                         .addComponent(labelvalorLuzGrande, javax.swing.GroupLayout.PREFERRED_SIZE,115, javax.swing.GroupLayout.PREFERRED_SIZE)
//                         .addGap(8,8,8)
                         .addComponent(valorLuzGrande, javax.swing.GroupLayout.PREFERRED_SIZE,68, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                        .addGap(16, 16, 16)
                        .addComponent(labelImagen1, javax.swing.GroupLayout.PREFERRED_SIZE,80, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(16, 16, 16)
                        .addComponent(labelImagen2, javax.swing.GroupLayout.PREFERRED_SIZE,80, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                    		 .addGap(18,18,18)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(palo1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(palo2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(26, 26, 26)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(numero2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(numero1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap(37, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER)
            .addGroup(layout.createSequentialGroup()
                .addComponent(labelCartas, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(palo1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(numero1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(palo2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(numero2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(labelImagen1, javax.swing.GroupLayout.PREFERRED_SIZE, 110, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(labelImagen2, javax.swing.GroupLayout.DEFAULT_SIZE, 90, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(labelvalorLuzGrande, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(valorLuzGrande, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSeparator1, javax.swing.GroupLayout.PREFERRED_SIZE,20, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(labelJugador1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(luzGrande, javax.swing.GroupLayout.Alignment.TRAILING))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                     .addComponent(labelApostadas1, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
                     .addComponent(fichasApostadasJugador, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE))
                 .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                   	.addComponent(labelFichas1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(fichasJugador, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
               		.addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSeparator2, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(labelJugador2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(personalidadOponente, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(labelApostadas2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent( fichasApostadasOponente, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(labelFichas2, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(fichasOponente, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(28, 28, 28)
                .addComponent(buttonRecomendar)
                .addGap(18, 18,18)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void palo1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_palo1ActionPerformed
        carta1.setSuit(carta1.getSuit(mapSuit.get((String)palo1.getSelectedItem())));
        updateLabel (carta1,labelImagen1);
        return;
}//GEN-LAST:event_palo1ActionPerformed

    private void palo2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_palo2ActionPerformed
    	  carta2.setSuit(carta2.getSuit(mapSuit.get((String)palo2.getSelectedItem())));
        updateLabel (carta2,labelImagen2);
        return;
}//GEN-LAST:event_palo2ActionPerformed

//    private void menuItemReiniciarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_menuItemReiniciarActionPerformed
//     
//      this.reset();
//      return;
//    }//GEN-LAST:event_menuItemReiniciarActionPerformed

//    public void reset (){
//      this.setVisible(false);
////      new Principal().setVisible(true); 
//      return;
//    }
    private void palo1ItemStateChanged(java.awt.event.ItemEvent evt) {//GEN-FIRST:event_palo1ItemStateChanged
        // DELETE
    }//GEN-LAST:event_palo1ItemStateChanged
    
    public void addRecomendationListener(java.awt.event.ActionListener listener){
    	buttonRecomendar.addActionListener(listener);
    }
    
    public void addResetButtonListener(java.awt.event.ActionListener listener){
    	menuItemReiniciar.addActionListener(listener);
    }

//    public void buttonRecomendarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_buttonRecomendarActionPerformed
//        
//        
//        /*
//         * 
//         * aqui tiene que ir el codigo del recomendador:
//         * Para obtener las carta1 y carta2:
//         * carta1.getPalo()   {devulve el string con el palo)
//         * carta2.getNumero() {devuelve un numero del 1 al 13)
//         * 
//         * para obtener si es luz grande:
//         * luzGrande.getState() [devuelve un booleando, verdadero si es luz grande}
//         * 
//         * para obtener las fichas: 
//         * fichasApostadasJugador.getValue()
//         * fichasApostadasOponente.getValue()
//         * fichasJugador.getValue()
//         * fichasOponente.getValue()
//         * (devuelve un int)
//         * 
//         * Para obtener la personalidad:
//         * personalidadOponente.getSelectedItem()
//         * (devuelve un String)
//         * 
//         * 
//         * 
//         * el text a recomendar esta justo abajo de este comentario
//         * 
//         * 
//         * 
//         * 
//         * 
//         */
//        
//    }//GEN-LAST:event_buttonRecomendarActionPerformed
    
    
    private void numero1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_numero1ActionPerformed
        carta1.setRank(carta1.getRank((String)numero1.getSelectedItem()));
        updateLabel (carta1,labelImagen1);
        return;
    }//GEN-LAST:event_numero1ActionPerformed

    private void numero2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_numero2ActionPerformed
    	  carta2.setRank(carta2.getRank((String)numero2.getSelectedItem()));
        updateLabel (carta2,labelImagen2);
        return;
    }//GEN-LAST:event_numero2ActionPerformed

//    private static final String IMAGE_PATH_FORMAT = "/images/card_%s.png"; 
    
    protected void updateLabel(Card carta,JLabel picture) {
    	
        ImageIcon icon = ResourceManager.getCardImage(carta);//createImageIcon("images/" + carta.toString() + ".gif");
     
        picture.setIcon(icon);
        if (icon != null) {
            picture.setText(null);
        } else {
            picture.setText("Image not found");
        }
    }
        
    protected static ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = Principal.class.getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
        }
    }
    
    
    
    public Card getCard1() {
		return carta1;
	}
	public Card getCard2() {
		return carta2;
	}
	public Integer getPlayerCoins(){
//		System.out.println("fichasJugador"+fichasJugador.getValue());
		return (Integer)fichasJugador.getValue();
	}
	public Integer getOpponentCoins(){
//		System.out.println("fichasOponente"+fichasOponente.getValue());
		return (Integer)fichasOponente.getValue();
	}
	public Integer getPlayerBetCoins(){
//		System.out.println("fichasApostadasJugador"+fichasApostadasJugador.getValue());
		return (Integer)fichasApostadasJugador.getValue();
	}
	public Integer getOpponentBetCoins(){
//		System.out.println("fichasApostadasOponente"+fichasApostadasOponente.getValue());
		return (Integer)fichasApostadasOponente.getValue();
	}
	public Boolean isPlayerBigBlind(){
//		System.out.println("isPlayerBigBlind"+luzGrande.isSelected());
		return luzGrande.isSelected();
	}
	public Integer getBigBlind(){
//		System.out.println("valorLuzGrande"+valorLuzGrande.getValue());
		return (Integer)valorLuzGrande.getValue();
	}
	public String getOpponentStrategy(){
		System.out.println("personalidadOponente"+personalidadOponente.getSelectedItem());
		return (String)personalidadOponente.getSelectedItem();
	}


	/**
     * @param args the command line arguments
     */
//    public static void main(String args[]) {
//        java.awt.EventQueue.invokeLater(new Runnable() {
//
//            public void run() {
//                new Principal().setVisible(true);
//            }
//        });
//    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton buttonRecomendar;
    private javax.swing.JSpinner fichasApostadasJugador;
    private javax.swing.JSpinner fichasApostadasOponente;
    private javax.swing.JSpinner fichasJugador;
    private javax.swing.JSpinner valorLuzGrande;
    private JLabel labelvalorLuzGrande;
    private javax.swing.JSpinner fichasOponente;
    private javax.swing.JMenuBar jMenuBar1;
    private javax.swing.JSeparator jSeparator1;
    private javax.swing.JSeparator jSeparator2;
    private JLabel labelApostadas1;
    private JLabel labelApostadas2;
    private JLabel labelCartas;
    private JLabel labelFichas1;
    private JLabel labelFichas2;
    private javax.swing.JLabel labelImagen1;
    private javax.swing.JLabel labelImagen2;
    private JLabel labelJugador1;
    private JLabel labelJugador2;
    private javax.swing.JCheckBox luzGrande;
    private javax.swing.JMenu menuArchivo;
    private javax.swing.JMenuItem menuItemReiniciar;
    private javax.swing.JComboBox numero1;
    private javax.swing.JComboBox numero2;
    private javax.swing.JComboBox palo1;
    private javax.swing.JComboBox palo2;
    private javax.swing.JComboBox personalidadOponente;
    // End of variables declaration//GEN-END:variables
}