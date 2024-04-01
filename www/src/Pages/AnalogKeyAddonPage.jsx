import React, { useContext, useEffect, useState } from 'react';
import { AppContext } from '../Contexts/AppContext';
import { Row, Stack, Button, Form } from 'react-bootstrap';
import { Formik, useFormikContext } from 'formik';
import * as yup from 'yup';
import { useTranslation } from 'react-i18next';

import Section from '../Components/Section';
import FormSelect from '../Components/FormSelect';
import WebApi from '../Services/WebApi';
import { getButtonLabels, BUTTONS, BUTTON_MASKS } from '../Data/Buttons';

const BOTTOM_MAGNETIC_POLE = [
	{ label: 'N Pole', value: 0 },
	{ label: 'S Pole', value: 1 }
];

const ACTUATION_MODE = [
	{ label: 'Static Actuation', value: 0 },
	{ label: 'Rapid Trigger', value: 1 },
	{ label: 'Continuous Rapid Trigger', value: 2 },
];

const schema = yup.object().shape({
	travelDistance: yup.number(),
	bottomMagneticPole: yup.number(),
	rappySnappy: yup.number(),
	actuationOptions: yup.object().shape({
		actuationMode: yup.number(),
		actuationPoint: yup.number(),
		pressSensitivity: yup.number(),
		releaseSensitivity: yup.number(),
	}),
	analogKeys: yup.array().of(
		yup.object().shape({
			mask: yup.number(),
			enabledPerKeySettings: yup.number(),
			actuationOptions: yup.object().shape({
				actuationMode: yup.number(),
				actuationPoint: yup.number(),
				pressSensitivity: yup.number(),
				releaseSensitivity: yup.number(),
			}),
		}),
	),
});

const defaultValues = {
	travelDistance: 400,
	bottomMagneticPole: 0,
	rappySnappy: 0,
	actuationOptions: {
		actuationMode: 0,
		actuationPoint: 150,
		pressSensitivity: 20,
		releaseSensitivity: 55,
	},
	analogKeys: [...Array(16)].map(() => ({
		mask: 0,
		enabledPerKeySettings: 0,
		actuationOptions: {
			actuationMode: 0,
			actuationPoint: 150,
			pressSensitivity: 20,
			releaseSensitivity: 55,
		},
	})),
};

const FormContext = () => {
	const { values, setValues } = useFormikContext();
	const { setLoading } = useContext(AppContext);

	useEffect(() => {
		async function fetchData() {
			const options = await WebApi.getAnalogKeyAddonOptions(setLoading);
			setValues(options);
		}
		fetchData();
	}, [setValues]);

	/*
	useEffect(() => {
		setValues(values);
	}, [values, setValues]);
	*/

	return null;
};

const ActuationSettings = (props) => {
	const {
		id,
		mask,
		travelDistance,
		actuationOptions,
		handleChange,
		setFieldValue,
	} = props;
	const {
		actuationMode,
		actuationPoint,
		pressSensitivity,
		releaseSensitivity,
	} = actuationOptions;
	const { t } = useTranslation('');

	return (
		<div hidden={mask === 0}>
			<Row className="mt-3">
				<FormSelect
					label={t('AnalogKeyAddon:analog-key.actuation-mode-label')}
					controlId={`${id}.actuationMode`}
					className="form-select-sm"
					groupClassName="col-sm-3"
					value={actuationMode}
					onChange={(e) => {
						const value = parseInt(e.target.value);

						setFieldValue(`${id}.actuationMode`, value);
					}}
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
				<Form.Group className="col-sm-3" controlId={`${id}.actuationPoint`}>
					<Form.Label>{t('AnalogKeyAddon:analog-key.actuation-point-label')}</Form.Label>
						<Stack direction="horizontal" gap={2} className="justify-content-center mt-1">
							<Form.Range
							value={actuationPoint}
							onChange={handleChange}
							min={10}
							max={travelDistance}
							step={10}
						/>
						<div>{`${(actuationPoint / 100).toFixed(2)}mm`}</div>
						</Stack>
				</Form.Group>
				<Form.Group className="col-sm-3" controlId={`${id}.pressSensitivity`} hidden={actuationMode == 0}>
					<Form.Label>{t('AnalogKeyAddon:analog-key.press-sensitivity-label')}</Form.Label>
					<Stack direction="horizontal" gap={2} className="justify-content-center mt-1">
						<Form.Range
							value={pressSensitivity}
							onChange={handleChange}
							min={15}
							max={Math.min(235, travelDistance < 15 ? 15 : travelDistance)}
							step={5}
						/>
						<div>{`${(pressSensitivity / 100).toFixed(2)}mm`}</div>
						</Stack>
				</Form.Group>
				<Form.Group className="col-sm-3" controlId={`${id}.releaseSensitivity`} hidden={actuationMode == 0}>
					<Form.Label>{t('AnalogKeyAddon:analog-key.release-sensitivity-label')}</Form.Label>
					<Stack direction="horizontal" gap={2} className="justify-content-center mt-1">
						<Form.Range
							value={releaseSensitivity}
							onChange={handleChange}
							min={15}
							max={Math.min(235, travelDistance < 15 ? 15 : travelDistance)}
							step={5}
						/>
						<div>{`${(releaseSensitivity / 100).toFixed(2)}mm`}</div>
						</Stack>
				</Form.Group>
			</Row>
		</div>
	);
};

const AnalogKeySettings = (props) => {
	const {
		label,
		id,
		buttonLabelType,
		mask,
		enabledPerKeySettings,
		setFieldValue,
	} = props;

	const { t } = useTranslation('');

	return (
		<div>
			<h1 className="mb-3">{label}</h1>
			<Row className="mb-3">
				<Form.Group className="col-sm-3">
					<Form.Label>{t('AnalogKeyAddon:analog-key.key-assign-label')}</Form.Label>
					<div>
						<Form.Select
							size="sm"
							name={`${id}.mask`}
							className="form-control col-sm-auto"
							value={mask}
							onChange={(e) => {
								const value = parseInt(e.target.value);

								setFieldValue(`${id}.mask`, value);
							}}
						>
							{BUTTON_MASKS.map((o, i) => (
								<option key={`${id}.mask[${i}]`} value={o.value}>
									{BUTTONS[buttonLabelType][o.label] || o.label}
								</option>
							))}
						</Form.Select>
					</div>
				</Form.Group>
				<Form.Group className="col-sm-3" controlId={`${id}.enabledPerKeySettings`} hidden={mask === 0}>
					<Form.Label>&nbsp;</Form.Label>
					<Form.Check
						name={`${id}.enabledPerKeySettings`}
						label={t('AnalogKeyAddon:analog-key.enabled-per-key-settings')}
						type="switch"
						className="form-select-sm"
						checked={enabledPerKeySettings}
						onChange={(e) => {
							setFieldValue(`${id}.enabledPerKeySettings`, e.target.checked ? 1 : 0);
						}}
						isInvalid={false}
					/>
				</Form.Group>
			</Row>
			{enabledPerKeySettings ? <ActuationSettings {...props} id={`${id}.actuationOptions`} /> : null}
		</div>
	);
};

export default function SettingsPage() {
	const { buttonLabels } = useContext(AppContext);
	const [saveMessage, setSaveMessage] = useState('');

	const saveSettings = async (values) => {
		const success = await WebApi.setAnalogKeyAddonOptions(values);
		setSaveMessage(
			success
				? t('Common:saved-success-message')
				: t('Common:saved-error-message'),
		);
	};

	const onSuccess = async (values) => await saveSettings(values);

	const { buttonLabelType } = buttonLabels;

	const { t } = useTranslation('');

	return (
		<Formik
			validationSchema={schema}
			onSubmit={onSuccess}
			initialValues={defaultValues}
		>
			{({ handleSubmit, handleChange, values, errors, setFieldValue }) =>
				((window.values = values) && console.log('values', values)) ||
				console.log('errors', errors) || (
					<div>
						<Form noValidate onSubmit={handleSubmit}>
							<Section title={t('AnalogKeyAddon:header-text')}>
									<div>
										<h1>{t('AnalogKeyAddon:key-switch-options-label')}</h1>
										<Row className="mt-3">
											<Form.Group className="col-sm-3" controlId={`travelDistance`}>
												<Form.Label>{t('AnalogKeyAddon:travel-distance-label')}</Form.Label>
													<Stack direction="horizontal" gap={2} className="justify-content-center mt-1">
														<Form.Range
															value={values.travelDistance}
															onChange={(e) => {
																const value = parseInt(e.target.value);

																setFieldValue(`travelDistance`, value);

																if (values.actuationOptions.actuationPoint > value) {
																	setFieldValue(`actuationOptions.actuationPoint`, value);
																}
																if (values.actuationOptions.pressSensitivity > value) {
																	setFieldValue(`actuationOptions.pressSensitivity`, Math.max(value, 15));
																}
																if (values.actuationOptions.releaseSensitivity > value) {
																	setFieldValue(`actuationOptions.releaseSensitivity`, Math.max(value, 15));
																}

																values.analogKeys.forEach((key, i) => {
																	if (key.actuationOptions.actuationPoint > value) {
																		setFieldValue(`analogKeys[${i}].actuationOptions.actuationPoint`, value);
																	}
																	if (key.actuationOptions.pressSensitivity > value) {
																		setFieldValue(`analogKeys[${i}].actuationOptions.pressSensitivity`, Math.max(value, 15));
																	}
																	if (key.actuationOptions.releaseSensitivity > value) {
																		setFieldValue(`analogKeys[${i}].actuationOptions.releaseSensitivity`, Math.max(value, 15));
																	}
																});
															}}
															min={10}
															max={400}
															step={10}
														/>
														<div>{`${(values.travelDistance / 100).toFixed(2)}mm`}</div>
													</Stack>
											</Form.Group>
											<FormSelect
												label={t('AnalogKeyAddon:bottom-magnetic-pole-label')}
												controlId={`bottomMagneticPole`}
												className="form-select-sm"
												groupClassName="col-sm-3"
												value={values.bottomMagneticPole}
												onChange={(e) => {
													const value = parseInt(e.target.value);

													setFieldValue(`bottomMagneticPole`, value);
												}}
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
										<h1 className="mt-3">{t('AnalogKeyAddon:common-actuation-options-label')}</h1>
										<ActuationSettings
											id={`actuationOptions`}
											buttonLabelType={buttonLabelType}
											handleChange={handleChange}
											setFieldValue={setFieldValue}
											{...values}
										/>
										<Form.Group className="mt-3" controlId={`rappySnappy`}>
											<Form.Check
												label={t('AnalogKeyAddon:rappy-snappy-label')}
												type="switch"
												className="form-select-sm"
												checked={values.rappySnappy}
												onChange={(e) => {
													setFieldValue(`rappySnappy`, e.target.checked ? 1 : 0);
												}}
											/>
										</Form.Group>
									</div>
									<hr className="mt-3" />
									{values.analogKeys && values.analogKeys.map((props, i) => (
										<>
											<AnalogKeySettings
												label={`Key ${i + 1} Options`}
												id={`analogKeys[${i}]`}
												buttonLabelType={buttonLabelType}
												errors={errors?.analogKeys?.at(i)}
												handleChange={handleChange}
												setFieldValue={setFieldValue}
												travelDistance={values.travelDistance}
												{...props}
											/>
											{values.analogKeys.length == i + 1 ? (
												<></>
											) : (
												<hr className="mt-3" />
											)}
										</>
									))}
							</Section>
							<Button type="submit">{t('Common:button-save-label')}</Button>
							{saveMessage ? (
								<span className="alert">{saveMessage}</span>
							) : null}
							<FormContext />
						</Form>
					</div>
				)
			}
		</Formik>
	);
}
