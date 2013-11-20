package ar.fi.uba.cim2.model;

import javax.swing.JSpinner;

public class Configuracion {
	//filtrado
	Integer tiempoFiltrado;
	Integer revolucionAgitado;
	//Tratamiento biologico
	Integer tiempoManteniento;
	Double proporcioEvacuacion;
	//desinfeccion
	Integer tiempoExposicionUV;
	Double porccentajeCLoro;
	
	
	
	JSpinner tiempoFiltradojs;
	JSpinner revolucionAgitadojs;
	//Tratamiento biologico
	JSpinner tiempoMantenientojs;
	JSpinner proporcioEvacuacionjs;
	//desinfeccion
	JSpinner tiempoExposicionUVjs;
	JSpinner porccentajeCLorojs;
	
	
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
