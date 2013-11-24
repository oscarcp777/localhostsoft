package ar.fi.uba.cim2.view;


import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class PanelEspera extends JPanel {
    JProgressBar barra = new JProgressBar();
    JButton btArrancar = new JButton();
    JButton btParar = new JButton();

    public PanelEspera() {
        setLayout( null );

        barra.setBounds( 5,10,295,25 );
        add( barra );

        btArrancar.setText( " Arrancar ");
        btArrancar.setBounds( 20,50,100,25 );
        add( btArrancar );
        btArrancar.addActionListener( new ActionListener() {
            public void actionPerformed( ActionEvent evt ) {
                btArrancar.setEnabled( false );
                btParar.setEnabled( true );
                UIManager.put( "ProgressBar.repaintInterval",new Integer(250) );
                // Ciclo de tiempo
                UIManager.put( "ProgressBar.cycleTime",new Integer(6000) );
                barra.setIndeterminate( true );
            }
        } );

        btParar.setText( " Parar " );
        btParar.setEnabled( false );
        btParar.setBounds( 185,50,100,25 );
        add( btParar );
        btParar.addActionListener( new ActionListener() {
            public void actionPerformed( ActionEvent evt ) {
                // Detenemos el movimiento de la barra
                barra.setIndeterminate( false );
                btArrancar.setEnabled( true );
                btParar.setEnabled( false );
            }
        } );
    }

    public static void main( String args[] ) {
        JFrame frame = new JFrame( "Tutorial de Java, Swing" );
        frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        frame.getContentPane().add( new PanelEspera(),BorderLayout.CENTER );
        frame.setSize( 315,120 );
        frame.setVisible( true );
    }
}