package fi.uba.drools.poker.example;

public class Cliente {
	 String nombre;
	 boolean registrado;
	 float gasto;
	 float descuento;
	public String getNombre() {
		return nombre;
	}
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}
	public boolean isRegistrado() {
		return registrado;
	}
	public void setRegistrado(boolean registrado) {
		this.registrado = registrado;
	}
	public float getGasto() {
		return gasto;
	}
	public void setGasto(float gasto) {
		this.gasto = gasto;
	}
	public float getDescuento() {
		return descuento;
	}
	public void setDescuento(float descuento) {
		this.descuento = descuento;
	}
}
