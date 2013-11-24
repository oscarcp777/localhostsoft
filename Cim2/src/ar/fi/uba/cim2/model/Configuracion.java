package ar.fi.uba.cim2.model;

import javax.swing.JLabel;
import javax.swing.JSpinner;
import javax.swing.JTextArea;

public class Configuracion {
	//filtrado
	Integer tiempoFiltrado=0;
	Integer revolucionAgitado=0;
	//Tratamiento biologico
	Integer tiempoManteniento=0;
	Double proporcioEvacuacion=0.0;
	//desinfeccion
	Integer tiempoExposicionUV=0;
	Double porccentajeCLoro=0.0;
	
	
	
	JSpinner tiempoFiltradojs;
	JSpinner revolucionAgitadojs;
	//Tratamiento biologico
	JSpinner tiempoMantenientojs;
	JSpinner proporcioEvacuacionjs;
	//desinfeccion
	JSpinner tiempoExposicionUVjs;
	JSpinner porccentajeCLorojs;
	JLabel htmlTextArea;
	
	public JLabel getHtmlTextArea() {
		return htmlTextArea;
	}
	public void setHtmlTextArea(JLabel htmlTextArea) {
		this.htmlTextArea = htmlTextArea;
	}
	public JSpinner getTiempoFiltradojs() {
		return tiempoFiltradojs;
	}
	public void setTiempoFiltradojs(JSpinner tiempoFiltradojs) {
		this.tiempoFiltradojs = tiempoFiltradojs;
	}
	public JSpinner getRevolucionAgitadojs() {
		return revolucionAgitadojs;
	}
	public void setRevolucionAgitadojs(JSpinner revolucionAgitadojs) {
		this.revolucionAgitadojs = revolucionAgitadojs;
	}
	public JSpinner getTiempoMantenientojs() {
		return tiempoMantenientojs;
	}
	public void setTiempoMantenientojs(JSpinner tiempoMantenientojs) {
		this.tiempoMantenientojs = tiempoMantenientojs;
	}
	public JSpinner getProporcioEvacuacionjs() {
		return proporcioEvacuacionjs;
	}
	public void setProporcioEvacuacionjs(JSpinner proporcioEvacuacionjs) {
		this.proporcioEvacuacionjs = proporcioEvacuacionjs;
	}
	public JSpinner getTiempoExposicionUVjs() {
		return tiempoExposicionUVjs;
	}
	public void setTiempoExposicionUVjs(JSpinner tiempoExposicionUVjs) {
		this.tiempoExposicionUVjs = tiempoExposicionUVjs;
	}
	public JSpinner getPorccentajeCLorojs() {
		return porccentajeCLorojs;
	}
	public void setPorccentajeCLorojs(JSpinner porccentajeCLorojs) {
		this.porccentajeCLorojs = porccentajeCLorojs;
	}
	public Integer getTiempoFiltrado() {
		return tiempoFiltrado;
	}
	public void setTiempoFiltrado(Integer tiempoFiltrado) {
		this.tiempoFiltrado = tiempoFiltrado;
	}
	public Integer getRevolucionAgitado() {
		return revolucionAgitado;
	}
	public void setRevolucionAgitado(Integer revolucionAgitado) {
		this.revolucionAgitado = revolucionAgitado;
	}
	public Integer getTiempoManteniento() {
		return tiempoManteniento;
	}
	public void setTiempoManteniento(Integer tiempoManteniento) {
		this.tiempoManteniento = tiempoManteniento;
	}
	public Double getProporcioEvacuacion() {
		return proporcioEvacuacion;
	}
	public void setProporcioEvacuacion(Double proporcioEvacuacion) {
		this.proporcioEvacuacion = proporcioEvacuacion;
	}
	public Integer getTiempoExposicionUV() {
		return tiempoExposicionUV;
	}
	public void setTiempoExposicionUV(Integer tiempoExposicionUV) {
		this.tiempoExposicionUV = tiempoExposicionUV;
	}
	public Double getPorccentajeCLoro() {
		return porccentajeCLoro;
	}
	public void setPorccentajeCLoro(Double porccentajeCLoro) {
		this.porccentajeCLoro = porccentajeCLoro;
	}
	public void updateParam() {
		this.tiempoFiltrado=(Integer) tiempoFiltradojs.getValue();
		this.revolucionAgitado=(Integer) revolucionAgitadojs.getValue();
		this.tiempoManteniento=(Integer) tiempoMantenientojs.getValue();
		this.proporcioEvacuacion=(Double) proporcioEvacuacionjs.getValue();
		this.tiempoExposicionUV=(Integer) tiempoExposicionUVjs.getValue();
		this.porccentajeCLoro=(Double) porccentajeCLorojs.getValue();
		
	}
}
