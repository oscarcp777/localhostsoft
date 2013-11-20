package ar.fi.uba.cim2.model;

import javax.swing.Icon;

public class Fuente {
	
	private String str;
    private boolean isSelected;
	private Integer capacidad;
	private Icon icon;
	
	public Fuente(String str, Integer capacidad) {
		super();
		this.str = str;
		this.isSelected = false;
		this.capacidad = capacidad;
	}
	@Override
	public String toString() {
		return str;
	}
	public String getStr() {
		return str;
	}
	public void setStr(String str) {
		this.str = str;
	}
	public boolean isSelected() {
		return isSelected;
	}
	public void setSelected(boolean isSelected) {
		this.isSelected = isSelected;
	}
	public Integer getCapacidad() {
		return capacidad;
	}
	public void setCapacidad(Integer capacidad) {
		this.capacidad = capacidad;
	}
	 public void setIcon(Icon icon) {
	      this.icon = icon;
	    }

	    public Icon getIcon() {
	      return icon;
	    }

}
