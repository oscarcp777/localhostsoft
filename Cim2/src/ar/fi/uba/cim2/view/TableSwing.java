package ar.fi.uba.cim2.view;
//Imports are listed in full to show what's being used
//could just import javax.swing.* and java.awt.* etc..
import java.awt.Color;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JTable;
import javax.swing.JScrollPane;
import javax.swing.JComboBox;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.TableColumn;
import javax.swing.DefaultCellEditor;

public class TableSwing {

  //Note: Typically the main method will be in a
  //separate class. As this is a simple one class
  //example it's all in the one class.
  public static void main(String[] args) {
   
       //Use the event dispatch thread for Swing components
       EventQueue.invokeLater(new Runnable()
       {
           
          @Override
           public void run()
           {
               
               new TableSwing();         
           }
       });
            
  }
  
  public TableSwing()
  {
      JFrame guiFrame = new JFrame();
      
      //make sure the program exits when the frame closes
      guiFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      guiFrame.setTitle("Disponibilidad de Agua");
      guiFrame.setSize(700,400);
    
      //This will center the JFrame in the middle of the screen
      guiFrame.setLocationRelativeTo(null);
      
      //Create the JTable using the ExampleTableModel implementing 
      //the AbstractTableModel abstract class
      JTable table = new JTable(new ExampleTableModel());
      
      //Set the column sorting functionality on
      table.setAutoCreateRowSorter(true);
      
      //Uncomment the next line if you want to turn the grid lines off
    //  table.setShowGrid(false);
      
      //Change the colour of the table - yellow for gridlines 
      //blue for background
      table.setGridColor(Color.DARK_GRAY);
      table.setBackground(Color.GRAY);
      
      
     
      //set the Event column to be larger than the rest and the Place column 
      //to be smaller
      TableColumn eventColumn = table.getColumnModel().getColumn(0);
      eventColumn.setMinWidth(150);
      
      TableColumn placeColumn = table.getColumnModel().getColumn(1);
      placeColumn.setMinWidth(150);
      
      //Place the JTable object in a JScrollPane for a scrolling table
      JScrollPane tableScrollPane = new JScrollPane(table);
      
      guiFrame.add(tableScrollPane);
      guiFrame.setVisible(true);
  }
  
  //implement a table model by extending a class to use
  //the AbstractTableModel
  class ExampleTableModel extends AbstractTableModel{
      
      //Two arrays used for the table data
      String[] columnNames = {"Fuentes ", "Capacidad" };
      
      Object[][] data = {
          {"Tanque de Agua Gris", "Filho"},
          {"Filtrado", "Filho"},
          {"CŽsar Cielo", "Filho"},
          {"CŽsar Cielo", "Filho"},
          {"CŽsar Cielo", "Filho"},
          {"CŽsar Cielo", "Filho"}
         
      };
      
      @Override
      public int getRowCount()
      {
          return data.length;
      }
      
      @Override
      public int getColumnCount()            
      {
          return columnNames.length;
      }
      
      @Override
      public Object getValueAt(int row, int column)
      {        
          return data[row][column];
      }
      
      //Used by the JTable object to set the column names
      @Override
      public String getColumnName(int column) {
          return columnNames[column];
      }
      
      //Used by the JTable object to render different
      //functionality based on the data type
      @Override
      public Class getColumnClass(int c) {
          return getValueAt(0, c).getClass();
      }
      
      @Override
      public boolean isCellEditable(int row, int column)
      {
         if (column == 0 || column == 1)
	   {
	        return false;
	   }
	   else
	   {
		return true;
	   }
      }
      
 
  }       
  
}

