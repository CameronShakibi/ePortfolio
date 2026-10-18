package appointments;

import java.util.Date;

public class Appointment { 
	
	//required variables
	private String aptID;
	private Date aptDate;
	private String aptDescription;
	
	//constructor
	public Appointment(String aptID, Date aptDate
			, String aptDescription) {

		
		if (aptID == null || aptID.length() > 10) {
			throw new IllegalArgumentException("Invalid appointment ID input.");
		}
		
		if (aptDate == null || aptDate.before(new Date())) {
			throw new IllegalArgumentException("Invalid appointment date input.");
		}
		
		if (aptDescription == null || aptDescription.length() > 50) {
			throw new IllegalArgumentException("Invalid appointment description input.");
		}
		
		this.aptID = aptID;
		this.aptDate = aptDate;
		this.aptDescription = aptDescription;
	}

	//Setters and Getters
	public Date getAptDate() {
		return aptDate;
	}

	public void setAptDate(Date aptDate) {
		this.aptDate = aptDate;
	}

	public String getAptDescription() {
		return aptDescription;
	} 

	public void setAptDescription(String aptDescription) {
		this.aptDescription = aptDescription;
	}

	public String getAptID() {
		return aptID;
	}
}
