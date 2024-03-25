import React from 'react';
import { Form } from 'react-bootstrap';

const FormSelect = ({ label, error, groupClassName, controlId, ...props }) => {
	return (
		<Form.Group className={groupClassName} controlId={controlId}>
			{label && <Form.Label>{label}</Form.Label>}
			<Form.Select {...props} />
			<Form.Control.Feedback type="invalid">{error}</Form.Control.Feedback>
		</Form.Group>
	);
};

export default FormSelect;
