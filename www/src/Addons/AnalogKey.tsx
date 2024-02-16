import React from 'react';
import { useTranslation } from 'react-i18next';
import { Form, Row, Stack } from 'react-bootstrap';
import * as yup from 'yup';

import Section from '../Components/Section';
import FormSelect from '../Components/FormSelect';

const ACTUATION_MODE = [
	{ label: 'Static Actuation', value: 0 },
	{ label: 'Rapid Trigger', value: 1 },
	{ label: 'Continuous Rapid Trigger', value: 2 },
];

const BOTTOM_MAGNETIC_POLE = [
	{ label: 'N Pole', value: 0 },
	{ label: 'S Pole', value: 1 }
];

export const analogKeyScheme = {
	AnalogKeyEnabled: yup.number().required().label('Analog Key Enabled'),
	travelDistance: yup
		.number()
		.label('Travel Distance')
		.validateRangeWhenValue('AnalogKeyEnabled', 10, 400),
	bottomMagneticPole: yup
		.number()
		.label('Bottom Magnetic Pole')
		.validateSelectionWhenValue('AnalogKeyEnabled', BOTTOM_MAGNETIC_POLE),
	actuationMode: yup
		.number()
		.label('Actuation Mode')
		.validateSelectionWhenValue('AnalogKeyEnabled', ACTUATION_MODE),
	actuationPoint: yup
		.number()
		.label('Actuation Point')
		.validateRangeWhenValue('AnalogKeyEnabled', 10, 400),
	pressSensitivity: yup
		.number()
		.label('Press Sensitivity')
		.validateRangeWhenValue('AnalogKeyEnabled', 15, 235),
	releaseSensitivity: yup
		.number()
		.label('Release Sensitivity')
		.validateRangeWhenValue('AnalogKeyEnabled', 15, 235),
};

export const analogKeyState = {
	AnalogKeyEnabled: 0,
	travelDistance: 400,
	bottomMagneticPole: 0,
  actuationMode: 0,
	actuationPoint: 150,
	pressSensitivity: 20,
	releaseSensitivity: 55,
};

const AnalogKey = ({ values, errors, handleChange, handleCheckbox, setFieldValue }) => {
	const { t } = useTranslation();

	const handleTravelDistance = (e) => {
		const travelDistance = e.target.value;
		handleChange(e);
		setFieldValue('actuationPoint', Math.min(travelDistance, values.actuationPoint));
		setFieldValue('pressSensitivity', Math.min(travelDistance, values.pressSensitivity));
		setFieldValue('releaseSensitivity', Math.min(travelDistance, values.releaseSensitivity));
	}

	return (
		<Section title={t('AddonsConfig:analog-key-header-text')}>
			<div id="AnalogKeyOptions" hidden={!values.AnalogKeyEnabled}>
		  	<Row className="mb-3">
				  <Form.Group className="col-sm-3 mb-3">
		      	<Form.Label>{t('AddonsConfig:analog-key-travel-distance-label')}</Form.Label>
							<Stack direction="horizontal" gap={2} className="justify-content-center mt-1">
								<Form.Range
								name="travelDistance"
								value={values.travelDistance}
								// isInvalid={errors.travelDistance}
								onChange={handleTravelDistance}
								min={10}
								max={400}
								step={10}
							/>
							<div>{`${(values.travelDistance / 100).toFixed(2)}mm`}</div>
							</Stack>
		      	<Form.Control.Feedback type="invalid">{errors.travelDistance}</Form.Control.Feedback>
	      	</Form.Group>
					<FormSelect
						label={t('AddonsConfig:analog-key-bottom-magnetic-pole-label')}
						name="bottomMagneticPole"
						className="form-select-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.bottomMagneticPole}
						error={errors.bottomMagneticPole}
						isInvalid={errors.bottomMagneticPole}
						onChange={handleChange}
					>
						{BOTTOM_MAGNETIC_POLE.map((o, i) => (
							<option
								key={`button-bottomMagneticPole-option-${i}`}
								value={o.value}
							>
								{o.label}
							</option>
						))}
					</FormSelect>
				</Row>
				<Row className="mb-3">
					<FormSelect
						label={t('AddonsConfig:analog-key-actuation-mode-label')}
						name="actuationMode"
						className="form-select-sm"
						groupClassName="col-sm-3 mb-3"
						value={values.actuationMode}
						error={errors.actuationMode}
						isInvalid={errors.actuationMode}
						onChange={handleChange}
					>
						{ACTUATION_MODE.map((o, i) => (
							<option
								key={`button-actuationMode-option-${i}`}
								value={o.value}
							>
								{o.label}
							</option>
						))}
					</FormSelect>
					<Form.Group className="col-sm-3 mb-3">
		      	<Form.Label>{t('AddonsConfig:analog-key-actuation-point-label')}</Form.Label>
							<Stack direction="horizontal" gap={2} className="justify-content-center mt-1">
								<Form.Range
								name="actuationPoint"
								value={values.actuationPoint}
								// isInvalid={errors.actuationPoint}
								onChange={handleChange}
								min={10}
								max={values.travelDistance}
								step={10}
							/>
							<div>{`${(values.actuationPoint / 100).toFixed(2)}mm`}</div>
							</Stack>
		      	<Form.Control.Feedback type="invalid">{errors.actuationPoint}</Form.Control.Feedback>
	      	</Form.Group>
				  <Form.Group className="col-sm-3 mb-3" hidden={values.actuationMode == 0}>
		      	<Form.Label>{t('AddonsConfig:analog-key-press-sensitivity-label')}</Form.Label>
						<Stack direction="horizontal" gap={2} className="justify-content-center mt-1">
							<Form.Range
								name="pressSensitivity"
								value={values.pressSensitivity}
								// isInvalid={errors.pressSensitivity}
								onChange={handleChange}
								min={15}
								max={Math.min(235, values.travelDistance)}
								step={5}
							/>
							<div>{`${(values.pressSensitivity / 100).toFixed(2)}mm`}</div>
							</Stack>
		      	<Form.Control.Feedback type="invalid">{errors.pressSensitivity}</Form.Control.Feedback>
	      	</Form.Group>
					<Form.Group className="col-sm-3 mb-3" hidden={values.actuationMode == 0}>
		      	<Form.Label>{t('AddonsConfig:analog-key-release-sensitivity-label')}</Form.Label>
						<Stack direction="horizontal" gap={2} className="justify-content-center mt-1">
							<Form.Range
								name="releaseSensitivity"
								value={values.releaseSensitivity}
								// isInvalid={errors.releaseSensitivity}
								onChange={handleChange}
								min={15}
								max={Math.min(235, values.travelDistance)}
								step={5}
							/>
							<div>{`${(values.releaseSensitivity / 100).toFixed(2)}mm`}</div>
							</Stack>
		      	<Form.Control.Feedback type="invalid">{errors.releaseSensitivity}</Form.Control.Feedback>
	      	</Form.Group>
				</Row>
			</div>
		</Section>
	);
};

export default AnalogKey;
